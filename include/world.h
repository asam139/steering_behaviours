//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __WORLD_H__
#define __WORLD_H__ 1

#include <mathlib/vec2.h>

#include <cstdio>

using MathLib::Vec2;

class World {
  public:
    World() {};
    ~World() {};

    Vec2 getWaypoint() const { return way_point_; };
    void setWayPoint(const Vec2& way_point) {
      way_point_ = way_point;
      printf("New WayPoint [%d, %d]\n", (uint32_t)way_point.x(), (uint32_t)way_point.y());
    };
  private:
    Vec2 way_point_{ 0.0f, 0.0f };
};

#endif