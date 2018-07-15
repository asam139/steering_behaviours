//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <scene_seek.h>
#include <defines.h>

#include <cstdio>


void SceneSeek::init(World* world) {
  printf("Seek Scene Is Being Initialized\n");
  world_ = world;
  way_point_sprite_.loadFromFile(AGENT_RED_PATH);
  agent_.init(world, Body::Type::Green);
}

void SceneSeek::shutdown() {
  agent_.shutdown();
  way_point_sprite_.free();
  world_ = nullptr;
  printf("Seek Scene Has Been Shutdown\n");
}

void SceneSeek::update(const float dt) {
  agent_.update(dt);
}

void SceneSeek::handleMouseEvent(const SDL_Event e) {
  if (e.type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    world_->setWayPoint(Vec2(x, y));
    way_point_sprite_.setPosition(x, y);
  }
}

void SceneSeek::handleKeyEvent(const SDL_Keycode key) {
  switch (key) {
    case SDLK_1:
      agent_.setSteeringMode(Body::SteeringMode::Direct_Seek);
      printf("Behavior Of Agent Changed To Direct Seek\n");
      break;
    case SDLK_2:
      agent_.setSteeringMode(Body::SteeringMode::Seek);
      printf("Behavior Of Agent Changed To Seek\n");
          break;
    case SDLK_3:
      agent_.setSteeringMode(Body::SteeringMode::Direct_Flee);
          printf("Behavior Of Agent Changed To Direct Flee\n");
          break;
    case SDLK_4:
      agent_.setSteeringMode(Body::SteeringMode::Flee);
          printf("Behavior Of Agent Changed To Flee\n");
          break;
    case SDLK_5:
      agent_.setSteeringMode(Body::SteeringMode::Direct_Arrive);
          printf("Behavior Of Agent Changed To Direct Arrive\n");
          break;
    case SDLK_6:
      agent_.setSteeringMode(Body::SteeringMode::Arrive);
          printf("Behavior Of Agent Changed To Arrive\n");
          break;
  }
}

void SceneSeek::render() {
  way_point_sprite_.render();
  agent_.render();
}