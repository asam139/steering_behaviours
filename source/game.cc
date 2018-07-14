//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <game.h>
#include <window.h>
#include <defines.h>
#include <scene_seek.h>
#include <debug_draw.h>

#include <cstdio>

void Game::init() {
  font_ = TTF_OpenFont(FONT_FILE, FPS_FONT_SIZE);
  if (!font_) {
    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
  }

  fps_sprite_.setVisible(false);

  createScenes();
}

void Game::start() {
  uint32_t fps_time{ 0 };
  uint32_t fps_time_acc{ 0 };

  uint32_t next_game_tick = SDL_GetTicks();
  uint32_t update_loops = 0;
  uint32_t render_loops = 0;

  const uint32_t skip_ticks = 1000 / TICKS_PER_SECOND;

  while (!quit_) {
    uint32_t loops = 0;
    while ((SDL_GetTicks() > next_game_tick) && (loops < MAX_FRAME_SKIP)) {
      handleInput();
      update(skip_ticks);

      next_game_tick += skip_ticks;
      ++loops;
      ++update_loops;
    }

    render();

    uint32_t c_time = SDL_GetTicks();
    fps_time_acc += (c_time - fps_time);
    fps_time = c_time;
    ++render_loops;
    if (render_loops > 100) {        //show stats each 100 frames
      const float fps = 1000.0f / (fps_time_acc / 100.0f);
      const float ratio = (float)render_loops / (float)update_loops;
      char text[255];
      sprintf_s(text, "%d RFPS      %d UFPS", (uint32_t)fps, (uint32_t)(fps / ratio));
      fps_sprite_.loadFromRenderedText(text, SDL_Color FOREGROUND_COLOR, font_, true);
      fps_sprite_.setVisible(true);

      render_loops = 0;
      update_loops = 0;
      fps_time_acc = 0;
    }
  }
}

void Game::shutdown() {
  scenes_[curr_scene_]->shutdown();
  for (uint8_t i = 0; i < SCENE_NUMBER; ++i) {
    delete scenes_[i];
  }
}

void Game::handleInput() {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      quit_ = true;
    }

    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
      scenes_[curr_scene_]->handleMouseEvent(e);
    }

    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_ESCAPE: quit_ = true; break;
        case SDLK_LEFT:   nextScene(-1); break;
        case SDLK_RIGHT:  nextScene(+1); break;
        case SDLK_DOWN:
          slo_mo_ = clamp<int8_t>(++slo_mo_, 1, 10);
          printf("Slow Motion Set To %d\n", slo_mo_);
        break;
        case SDLK_UP:
          slo_mo_ = clamp<int8_t>(--slo_mo_, 1, 10);
          printf("Slow Motion Set To %d\n", slo_mo_);
        break;
        case SDLK_d:
          DebugDraw::toggleEnabled();
          printf("Debug Draw Mode Changed\n");
        break;
      }
      scenes_[curr_scene_]->handleKeyEvent(e.key.keysym.sym);
    }
  }
}

void Game::update(const uint32_t dt) {
  scenes_[curr_scene_]->update(dt / slo_mo_);
}

void Game::render() {
  SDL_Renderer* renderer = Window::instance().getRenderer();
  SDL_SetRenderDrawColor(renderer, 0xD0, 0xD0, 0xD0, 0xFF);
  SDL_RenderClear(renderer);

  fps_sprite_.render();
  scenes_[curr_scene_]->render();

  SDL_RenderPresent(renderer);
}

void Game::createScenes() {
  scenes_[0] = new SceneSeek();
  nextScene(0);
}

void Game::nextScene(const int8_t sign) {
  scenes_[curr_scene_]->shutdown();
  curr_scene_ += sign;
  curr_scene_ = clamp<int8_t>(curr_scene_, 0, SCENE_NUMBER - 1);
  scenes_[curr_scene_]->init(&world_);
}