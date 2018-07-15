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
#include <agent.h>

using MathLib::Vec2;

class World {
public:
    World() {
        target_.init(this, Body::Color::Red, Body::Type::Manual);
        ia_.init(this, Body::Color::Green, Body::Type::Autonomous);
        ia_.getKinematic()->position = Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    };
    ~World() {
        target_.shutdown();
        ia_.shutdown();
    };

    void update(const float dt) { target_.update(dt); ia_.update(dt); }
    void render() { target_.render(); ia_.render(); }

    Agent* target() { return &target_; }
    Agent* ia() { return &ia_; }
private:
    Agent target_, ia_;
};

#endif