//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __DEBUG_DRAW_H__
#define __DEBUG_DRAW_H__ 1
#include <vector>
#include <mathlib/vec2.h>
using MathLib::Vec2;

class DebugDraw {
public:
    DebugDraw() {};
    ~DebugDraw() {};

    static void render();

    static void drawVector(const Vec2& pos, const Vec2& v,
                           const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
    static void drawCross(const Vec2& pos,
                          const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
    static void drawPositionHist(const Vec2& pos);

    static void toggleEnabled() { enabled_ = !enabled_; };
private:
    static void renderVector(const Vec2& pos, const Vec2& v,
                             const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
    static void renderCross(const Vec2& pos,
                            const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
    static void renderPositionHist();

    static bool enabled_;
    static float delta_;

#define MAX_HIST 1000
    static uint16_t hist_idx_;
    static Vec2 hist_[MAX_HIST];

    enum class CommandType {
        Vector,
        Cross
    };

    struct Command {
        CommandType type;
        Vec2 pos;
        Vec2 dir;
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    static std::vector<Command> command_list_;
};


#endif