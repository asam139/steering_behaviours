//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __SCENE_H__
#define __SCENE_H__ 1

#include <world.h>

#include <cstdint>
#include <SDL/SDL.h>


class Scene {
  public:
    virtual ~Scene() {};

    virtual void init(World* world) = 0;
    virtual void shutdown() = 0;

    virtual void update(const float dt) = 0;
    virtual void handleMouseEvent(const SDL_Event e) = 0;
    virtual void handleKeyEvent(const SDL_Keycode key) = 0;
    virtual void render() = 0;
  protected:
    Scene() {};

    World* world_ = nullptr;
};

#endif