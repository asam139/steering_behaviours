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
#include <vector>
#include <memory>

using MathLib::Vec2;

class World {
public:
    World() {
        target_.init(this, Body::Color::Red, Body::Type::Manual);
        ia_.init(this, Body::Color::Green, Body::Type::Autonomous);

        const float _w = WINDOW_WIDTH * 0.5;
        const float _h = WINDOW_HEIGHT * 0.5;
        ia_.getKinematic()->position = Vec2(_w, _h);

        _agentArray_ptr = std::unique_ptr<std::vector<Agent *>>(new std::vector<Agent *>());


        for (int i = 0; i < 5; ++i) {
            Agent agent;
            agent.init(this, Body::Color::Blue, Body::Type::Autonomous);
            agent.getKinematic()->position = Vec2(_w  + randomFloat(-1, 1) * 10, _h + randomFloat(-1, 1) * 10);
            agent.setAgentGroup(*_agentArray_ptr);
            _agentArray_ptr->push_back(&ia_);
        }
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
    std::unique_ptr<std::vector<Agent *>> _agentArray_ptr;
    Agent target_, ia_;
};

#endif