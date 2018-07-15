//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <body.h>
#include <defines.h>
#include <debug_draw.h>

void Body::init(const Type type) {
  type_ = type;

  switch(type) {
    case Type::Green: sprite_.loadFromFile(AGENT_GREEN_PATH); break;
    case Type::Blue: sprite_.loadFromFile(AGENT_BLUE_PATH); break;
    case Type::Purple: sprite_.loadFromFile(AGENT_PURPLE_PATH); break;
    default: sprite_.loadFromFile(AGENT_GREEN_PATH);
  }

  steering_ = SteeringMode::Direct_Seek;
}

void Body::update(const float dt) {
  switch (steering_) {
    case SteeringMode::Direct_Seek: update_direct_seek(dt); break;
    case SteeringMode::Seek: update_seek(dt); break;
    case SteeringMode::Direct_Flee: update_direct_flee(dt); break;
    case SteeringMode::Flee: update_flee(dt); break;
    case SteeringMode::Direct_Arrive: update_direct_arrive(dt); break;
    default: update_direct_seek(dt); break;
  }

  sprite_.setPosition(position_.x(), position_.y());
}

void Body::render() const {
  sprite_.render();

  DebugDraw::drawVector(dd.red.pos, dd.red.v, 0xFF, 0x00, 0x00, 0xFF);
  DebugDraw::drawVector(dd.green.pos, dd.green.v, 0x00, 0x50, 0x00, 0xFF);
  DebugDraw::drawVector(dd.blue.pos, dd.blue.v, 0x00, 0x00, 0xFF, 0xFF);
  DebugDraw::drawPositionHist(position_);
}

void Body::setTarget(const Vec2& target) {
    target_ = target;
}

void Body::update_direct_seek(const float dt) {
    velocity_ = (target_ - position_).normalized() * max_velocity_ * dt;
    position_ = position_ + velocity_;

    dd.green.pos = position_;
    dd.green.v = velocity_ * 25.0f;

    dd.red.pos = position_;
    dd.red.v = Vec2 (0.0f, 0.0f);

    dd.blue.pos = position_;
    dd.blue.v = Vec2(0.0f, 0.0f);

}

void Body::update_seek(const float dt) {
    const Vec2 desired_velocity = (target_ - position_).normalized() * max_velocity_ * dt;
    const Vec2 steering = (desired_velocity - velocity_).trunc(max_steering_ * dt) / mass_;
    velocity_ = (velocity_ + steering).trunc(max_velocity_ * dt);
    position_ = position_ + velocity_;

    dd.green.pos = position_;
    dd.green.v = velocity_ * 25.0f;

    dd.blue.pos = position_;
    dd.blue.v = desired_velocity * 25.0f;

    dd.red.pos = position_ + (velocity_ * 25.0f);
    dd.red.v = steering * 100.0f;
}

void Body::update_direct_flee(const float dt) {
    velocity_ = (position_ - target_).normalized() * max_velocity_ * dt;
    position_ = position_ + velocity_;

    dd.green.pos = position_;
    dd.green.v = velocity_ * 25.0f;

    dd.red.pos = position_;
    dd.red.v = Vec2 (0.0f, 0.0f);

    dd.blue.pos = position_;
    dd.blue.v = Vec2(0.0f, 0.0f);
}

void Body::update_flee(const float dt) {
    const Vec2 desired_velocity = (position_ - target_).normalized() * max_velocity_ * dt;
    const Vec2 steering = (desired_velocity - velocity_).trunc(max_steering_ * dt) / mass_;
    velocity_ = (velocity_ + steering).trunc(max_velocity_ * dt);
    position_ = position_ + velocity_;
    rotation_ = 0.0f; //no rotation

    dd.green.pos = position_;
    dd.green.v = velocity_ * 25.0f;

    dd.blue.pos = position_;
    dd.blue.v = desired_velocity * 25.0f;

    dd.red.pos = position_ + (velocity_ * 25.0f);
    dd.red.v = steering * 100.0f;
}

void Body::update_direct_arrive(const float dt){
    //direction to the target
    velocity_ = target_ - position_;
    if (velocity_.length2() < sq_radius_) { //inside the radius
      velocity_.x() = 0.0f; //no velocity
      velocity_.y() = 0.0f;

    } else {
        velocity_ /= time_to_target_ * dt; //velocity adjusted to time
        if (velocity_.length() > max_velocity_ ) { //max out
            //normalized direction to max speed
            velocity_ = velocity_.normalized() * max_velocity_;
        }
    }

    position_ = position_ + velocity_;
    rotation_ = 0.0f; //no rotation*/

    dd.green.pos = position_;
    dd.green.v = velocity_ * 25.0f;

    dd.red.pos = position_;
    dd.red.v = Vec2 (0.0f, 0.0f);

    dd.blue.pos = position_;
    dd.blue.v = Vec2(0.0f, 0.0f);
}


