//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __SCENE_SEEK_H__
#define __SCENE_SEEK_H__ 1

#include <scene.h>
#include <sprite.h>
#include <agent.h>

class SceneSeek: public Scene {
  public:
    SceneSeek() {};
    ~SceneSeek() {};

    void init(World* world) final;
    void shutdown() final;

    void update(const float dt) final;
    void handleMouseEvent(const SDL_Event e) final;
    void handleKeyEvent(const SDL_Keycode key) final;
    void render() final;
  private:
    Sprite way_point_sprite_;
    Agent agent_;
};

#endif