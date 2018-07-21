//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <body.h>
#include <defines.h>
#include <debug_draw.h>
#include <agent.h>
#include <utils.h>
#include <movementUtils.h>

void Body::init(const Color color, const Type type) {
    _type = type;
    _color = color;

    switch(color) {
        case Color::Green: _sprite.loadFromFile(AGENT_GREEN_PATH); break;
        case Color::Blue: _sprite.loadFromFile(AGENT_BLUE_PATH); break;
        case Color::Purple: _sprite.loadFromFile(AGENT_PURPLE_PATH); break;
        case Color::Red: _sprite.loadFromFile(AGENT_RED_PATH); break;
        default: _sprite.loadFromFile(AGENT_GREEN_PATH);
    }

    _steering_mode = SteeringMode::Kinematic_Seek;
}

void Body::update(const float dt) {
    if (_type == Type::Autonomous) {
        updateAutonomous(dt);
    } else {
        updateManual(dt);
    }

    _sprite.setPosition(_state.position.x(), _state.position.y());
    _sprite.setRotation(_state.orientation);
}

void Body::updateAutonomous(const float dt) {
    switch (_steering_mode) {
        case SteeringMode::Kinematic_Seek: update_kinematic_seek(dt); break;
        case SteeringMode::Kinematic_Flee: update_kinematic_flee(dt); break;
        case SteeringMode::Kinematic_Arrive: update_kinematic_arrive(dt); break;
        case SteeringMode::Kinematic_Wander: update_kinematic_wander(dt); break;
        case SteeringMode::Seek: update_seek(dt); break;
        case SteeringMode::Flee: update_flee(dt); break;
        case SteeringMode::Arrive: update_arrive(dt); break;
        case SteeringMode::Align: update_align(dt); break;
        case SteeringMode::Velocity_Matching: update_velocity_matching(dt); break;
        case SteeringMode::Pursue: update_pursue(dt); break;
        default: update_kinematic_seek(dt); break;
    }

    _sprite.setPosition(_state.position.x(), _state.position.y());
}

void Body::updateManual(const float dt) {
    MathLib::Vec2 orientation;
    orientation.fromPolar(1.0f, _state.orientation);
    _state.velocity = orientation.normalized() * _state.speed;
    _state.position += _state.velocity * dt;

    keepInSpeed();
    keepInBounds();

    dd.green.pos = _state.position;
    dd.green.v = _state.velocity;
}

void Body::render() const {
  _sprite.render();

  DebugDraw::drawVector(dd.red.pos, dd.red.v, 0xFF, 0x00, 0x00, 0xFF);
  DebugDraw::drawVector(dd.green.pos, dd.green.v, 0x00, 0x50, 0x00, 0xFF);
  DebugDraw::drawVector(dd.blue.pos, dd.blue.v, 0x00, 0x00, 0xFF, 0xFF);
  DebugDraw::drawPositionHist(_state.position);
}

void Body::setTarget(Agent* target) {
    _target = target;
}

void Body::setOrientation(const Vec2& velocity) {
    if (velocity.length2() > 0) {
        _state.orientation = atan2(velocity.y(), velocity.x());
    }
}

void Body::keepInBounds() {
    if (_state.position.x() > WINDOW_WIDTH) _state.position.x() = 0.0f;
    if (_state.position.x() < 0.0f) _state.position.x() = WINDOW_WIDTH;
    if (_state.position.y() > WINDOW_HEIGHT) _state.position.y() = 0.0f;
    if (_state.position.y() < 0.0f) _state.position.y() = WINDOW_HEIGHT;
}

void Body::keepInSpeed() {
    if (_state.velocity.length() > _maxSpeed) {
        _state.velocity = _state.velocity.normalized() * _maxSpeed;
    }
}

void Body::updateKinematic(const float dt, const KinematicSteering& steering) {
    _state.acceleration = steering.acceleration;
    if (_state.acceleration.length() > _maxAcceleration) {
        _state.acceleration = _state.acceleration.normalized() * _maxAcceleration;
    }
    _state.velocity += _state.acceleration * dt;
    if (_state.velocity.length() > _maxSpeed) {
        _state.velocity = _state.velocity.normalized() * _maxSpeed;
    }

    _state.position += _state.velocity * dt;

    _state.angularAcceleration = steering.angularAcceleration;
    if (abs(_state.angularAcceleration) > _maxAngularSpeed) {
        _state.angularAcceleration = sign(_state.angularAcceleration) * _maxAngularSpeed;
    }
    _state.orientation += _state.angularAcceleration * dt;
}

void Body::update_kinematic_seek(const float dt) {
    MovementUtils::SeekCalculate(&_state, _target->getKinematic(), &_steering, _maxSpeed);

    updateKinematic(dt, _steering);

    dd.green.pos = _state.position;
    dd.green.v = _state.velocity * 25.0f;

    dd.red.pos = _state.position;
    dd.red.v = {0.0f, 0.0f};

    dd.blue.pos = _state.position;
    dd.blue.v = {0.0f, 0.0f};

}

void Body::update_seek(const float dt) {
    //aceeleration towards the target
    _steering.acceleration = (_target->getKinematic()->position - _state.position).normalized() * _maxAcceleration;
    _steering.angularAcceleration = 0.0f; //no angular

    updateKinematic(dt, _steering);

    dd.green.pos = _state.position;
    dd.green.v = _state.velocity * 25.0f;

    dd.blue.pos = _state.position;
    dd.blue.v = _steering.acceleration.normalized() * _maxSpeed * 25.0f;

    dd.red.pos = _state.position + (_state.velocity * 25.0f);
    dd.red.v = dd.blue.v - dd.green.v;
}

void Body::update_kinematic_flee(const float dt) {
    _state.acceleration = {0.0f, 0.0f};
    _state.velocity = (_state.position - _target->getKinematic()->position).normalized() * _maxSpeed;

    _steering.acceleration = {0.0f, 0.0f};
    _steering.angularAcceleration = 0.0f;

    updateKinematic(dt, _steering);

    dd.green.pos = _state.position;
    dd.green.v = _state.velocity * 25.0f;

    dd.red.pos = _state.position;
    dd.red.v = {0.0f, 0.0f};

    dd.blue.pos = _state.position;
    dd.blue.v = {0.0f, 0.0f};
}

void Body::update_flee(const float dt) {
    //aceeleration towards the target
    _steering.acceleration = (_state.position - _target->getKinematic()->position).normalized() * _maxAcceleration;
    _steering.angularAcceleration = 0.0f; //no angular

    updateKinematic(dt, _steering);

    dd.green.pos = _state.position;
    dd.green.v = _state.velocity * 25.0f;

    dd.blue.pos = _state.position;
    dd.blue.v = _steering.acceleration.normalized() * _maxSpeed * 25.0f;

    dd.red.pos = _state.position + (_state.velocity * 25.0f);
    dd.red.v = dd.blue.v - dd.green.v;
}

void Body::update_kinematic_arrive(const float dt) {
    _state.acceleration = {0.0f, 0.0f};

    //direction to the target
    const Vec2 direction = (_target->getKinematic()->position - _state.position);
    if (direction.length() < _minDistance) { //inside the radius
        _state.velocity = {0.0f, 0.0f};
    } else {
        _state.velocity = direction.normalized() * direction.length() / _fixedTime;
    }

    _steering.acceleration = {0.0f, 0.0f};
    _steering.angularAcceleration = 0.0f;

    updateKinematic(dt, _steering);


    dd.green.pos = _state.position;
    dd.green.v = _state.velocity * 25.0f;

    dd.red.pos = _state.position;
    dd.red.v = {0.0f, 0.0f};

    dd.blue.pos = _state.position;
    dd.blue.v = {0.0f, 0.0f};
}

void Body::update_arrive(const float dt){
    //direction to the target
    const Vec2 direction = (_target->getKinematic()->position - _state.position);
    const float distance = direction.length(); //distance to target

    float speed = _maxSpeed; //max speed
    if (distance < _slowRadius) { //inside the slow zone
        //speed slowing +down
        speed = (_maxSpeed * distance) / _slowRadius;
    }

    //velocity towards the target
    const Vec2 velocity = direction.normalized() * speed;
    //linear acceleration adjusted to time
    _steering.acceleration = (velocity - _state.velocity); // _fixedTime;
    _steering.angularAcceleration = 0.0f;

    updateKinematic(dt, _steering);

    dd.green.pos = _state.position;
    dd.green.v = _state.velocity * 25.0f;

    dd.red.pos = _state.position;
    dd.red.v = _state.acceleration * 50.0f;

    dd.blue.pos = _state.position;
    dd.blue.v = {0.0f, 0.0f};
}

void Body::update_kinematic_wander(const float dt) {
    Vec2 orientation;
    //orientation of character as vector
    orientation.fromPolar(1.0f, _state.orientation);

    _state.velocity = orientation * _maxSpeed; //max speed

    // rotate to random (binomial distribution around 0)
    _steering.acceleration = {0.0f, 0.0f};
    _steering.angularAcceleration = _maxRotation * RandomFloat(-1.0f, 1.0f);

    updateKinematic(dt, _steering);

    dd.green.pos = _state.position;
    dd.green.v = _state.velocity * 25.0f;

    dd.red.pos = _state.position;
    dd.red.v = {0.0f, 0.0f};

    dd.blue.pos = _state.position;
    dd.blue.v = {0.0f, 0.0f};
}

void Body::update_align(const float dt) {
    //rotation between character and target wrapped to (-PI, PI)
    const float rotation = WrapPosNegPI(_target->getKinematic()->orientation - _state.orientation);
    const float rotation_size = abs(rotation); //absolute value of rotation
    float target_rotation = _maxRotation; //max
    if (rotation_size < _slowAngle) { //inside the slow zone
        //speed of rotation slowing down
        target_rotation = (_maxRotation * rotation_size) / _slowAngle;
    }
    target_rotation *= sign(rotation); //positive or negative
    //angular acceleration adjusted to time
    _steering.angularAcceleration = (target_rotation) / _fixedTime;
    _steering.acceleration = {0.0f, 0.0f};

    _state.velocity = {0.0f, 0.0f};
    updateKinematic(dt, _steering);

    Vec2 orientation;
    //orientation of character as vector
    orientation.fromPolar(1.0f, _state.orientation);
    dd.green.pos = _state.position;
    dd.green.v = orientation * 100.0f;

    Vec2 targetOrientation;
    //orientation of character as vector
    targetOrientation.fromPolar(1.0f, _target->getKinematic()->orientation);
    dd.red.pos = _target->getKinematic()->position;
    dd.red.v = targetOrientation * 100.0f;

    dd.blue.pos = _state.position;
    dd.blue.v = {0.0f, 0.0f};
}

void Body::update_velocity_matching(const float dt) {
    _steering.acceleration = (_target->getKinematic()->velocity - _state.velocity) / _fixedTime;
    _steering.angularAcceleration = 0.0f;

    updateKinematic(dt, _steering);

    dd.green.pos = _state.position;
    dd.green.v = _state.velocity * 25.0f;

    dd.red.pos = _state.position;
    dd.red.v = _state.acceleration * 50.0f;

    dd.blue.pos = _state.position;
    dd.blue.v = {0.0f, 0.0f};
}

void Body::update_pursue(const float dt) {
    //distance to the target
    const float distance = (_target->getKinematic()->position - _state.position).length();
    float speed = _state.velocity.length(); //speed of character
    float prediction = _maxPrediction; //max prediction
    if (speed > (distance / _maxPrediction)) { //reasonable predicion
        prediction = distance / speed; //calc predicion time
    }
    KinematicStatus new_target = *_target->getKinematic(); //new target
    //position of new target
    new_target.position += _target->getKinematic()->velocity * prediction;

    //delegate to seek behavior with new target
    MovementUtils::SeekCalculate(&_state, &new_target, &_steering, _maxSpeed);
    updateKinematic(dt, _steering);

    dd.green.pos = _state.position;
    dd.green.v = _state.velocity * 25.0f;

    dd.red.pos = _state.position;
    dd.red.v = _state.acceleration * 50.0f;

    dd.blue.pos = _state.position;
    dd.blue.v = {0.0f, 0.0f};
}
