//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __DEFINES_H__
#define __DEFINES_H__ 1

#include <algorithm>
#include <mathlib/vec2.h>

#define NOMINMAX

#define GAME_NAME "Steering Behaviors Demo"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define TICKS_PER_SECOND 30
#define MAX_FRAME_SKIP 10

#define FOREGROUND_COLOR { 0, 0, 0, 255 }
#define SHADOW_COLOR {160, 160, 160, 255}

#define FONT_FILE "../media/8bit.ttf"
#define AGENT_BLUE_PATH "../media/agent_blue.png"
#define AGENT_RED_PATH "../media/agent_red.png"
#define AGENT_GREEN_PATH "../media/agent_green.png"
#define AGENT_PURPLE_PATH "../media/agent_purple.png"

#define FPS_FONT_SIZE 12

#define SCENE_NUMBER 1

template <typename T>
inline T clamp(const T& n, const T& lower, const T& upper) {
  return std::max(lower, std::min(n, upper));
}

inline MathLib::Vec2 rotate2D(const MathLib::Vec2& pivot, const MathLib::Vec2& point, const float angle) {
  const float s = sin(angle);
  const float c = cos(angle);

  return MathLib::Vec2(c * (point.x() - pivot.x()) - s * (point.y() - pivot.y()) + pivot.x(),
    s * (point.x() - pivot.x()) + c * (point.y() - pivot.y()) + pivot.y());
}

#endif