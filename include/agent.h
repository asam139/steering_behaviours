//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __AGENT_H__
#define __AGENT_H__ 1

#include <body.h>
#include <mind.h>

#include <cstdint>

class World;

class Agent {
  public:
    Agent() {};
    ~Agent() {};

    void init(World* world, const Body::Type type);
    void update(const float dt);
    void render() const;
    void shutdown();

    void setSteering(Body::Steering steering) { body_.setSteering(steering); }
  private:
    World * world_;

    Body body_;
    Mind mind_;
};

#endif