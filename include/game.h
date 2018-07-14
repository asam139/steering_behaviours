//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __GAME_H__
#define __GAME_H__ 1

#include <sprite.h>
#include <scene.h>
#include <defines.h>
#include <world.h>

class Game {
  public:
    Game() {};
    ~Game() {};

    void init();
    void start();
    void shutdown();
  private:
    void handleInput();
    void update(const uint32_t dt);
    void render();

    void createScenes();
    void nextScene(const int8_t sign);

    bool quit_ = false;
    Sprite fps_sprite_;
    TTF_Font* font_ = nullptr;

    int8_t curr_scene_ = 0;
    Scene* scenes_[SCENE_NUMBER];

    World world_;

    int8_t slo_mo_ = 1;
};

#endif