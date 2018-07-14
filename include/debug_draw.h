//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __DEBUG_DRAW_H__
#define __DEBUG_DRAW_H__ 1

#include <mathlib/vec2.h>
using MathLib::Vec2;

class DebugDraw {
  public:
    DebugDraw() {};
    ~DebugDraw() {};

    static void drawVector(const Vec2& pos, const Vec2& v,
      const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
    static void drawPositionHist(const Vec2& pos);
    static void toggleEnabled() { enabled_ = !enabled_; };
  private:
    static bool enabled_;
    static float delta_;

#define MAX_HIST 1000
    static uint16_t hist_idx_;
    static Vec2 hist_[MAX_HIST];
};

#endif