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

        for (int i = 0; i < 20; ++i) {
            auto agent_ptr = std::shared_ptr<Agent>(new Agent());

            agent_ptr->init(this, Body::Color::Blue, Body::Type::Autonomous);
            agent_ptr->getKinematic()->position = Vec2(_w  + randomFloat(-1, 1) * 10, _h + randomFloat(-1, 1) * 10);
            agent_ptr->setAgentGroup(&_agentArray);
            _agentArray.push_back(agent_ptr);
        }
    };
    ~World() {
        target_.shutdown();
        ia_.shutdown();
        for (auto a : _agentArray) {
            a->shutdown();
        }
    };

    void update(const float dt) {
        target_.update(dt);
        ia_.update(dt);

        for (auto a : _agentArray) {
            a->update(dt);
        }
    }
    void render() {
        target_.render();
        ia_.render();

        for (auto a : _agentArray) {
            a->render();
        }
    }

    Agent* target() { return &target_; }
    Agent* ia() { return &ia_; }

    void setAISteering(Body::SteeringMode steering) {
        ia()->setSteering(steering);
        for (auto a : _agentArray) {
            a->setSteering(steering);
        }
    }
private:
    std::vector< std::shared_ptr< Agent > > _agentArray;
    Agent target_, ia_;
};

#endif