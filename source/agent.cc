//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <agent.h>
#include <world.h>

void Agent::init(World* world, const Body::Color color, const Body::Type type) {
  world_ = world;
  body_.init(color, type, this);
  mind_.init(world, &body_);
}

void Agent::shutdown() {
  world_ = nullptr;
}

void Agent::update(const float dt) {
  mind_.update(dt);
  body_.update(dt);
}

void Agent::render() const {
  body_.render();
}