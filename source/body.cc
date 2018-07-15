//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <body.h>
#include <defines.h>
#include <debug_draw.h>
#include <utils.h>

void Body::init(const Type type) {
    type_ = type;
    switch(type) {
        case Type::Green: sprite_.loadFromFile(AGENT_GREEN_PATH); break;
        case Type::Blue: sprite_.loadFromFile(AGENT_BLUE_PATH); break;
        case Type::Purple: sprite_.loadFromFile(AGENT_PURPLE_PATH); break;
        default: sprite_.loadFromFile(AGENT_GREEN_PATH);
    }
    steering_ = SteeringMode::Direct_Seek;


    _kinematicStatus.position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    _kinematicStatus.velocity = {0.0f, 0.0f};
    _kinematicStatus.rotation = 0.0f;

    _kinematicStatusTarget.position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

}

void Body::update(const float dt) {
  switch (steering_) {
    case SteeringMode::Direct_Seek: update_direct_seek(dt); break;
    case SteeringMode::Seek: update_seek(dt); break;
    case SteeringMode::Direct_Flee: update_direct_flee(dt); break;
    case SteeringMode::Flee: update_flee(dt); break;
    case SteeringMode::Direct_Arrive: update_direct_arrive(dt); break;
    case SteeringMode::Arrive: update_arrive(dt); break;
    case SteeringMode::Wandering: update_wandering(dt); break;
    default: update_direct_seek(dt); break;
  }

  sprite_.setPosition(_kinematicStatus.position.x(), _kinematicStatus.position.y());
}

void Body::render() const {
  sprite_.render();

  DebugDraw::drawVector(dd.red.pos, dd.red.v, 0xFF, 0x00, 0x00, 0xFF);
  DebugDraw::drawVector(dd.green.pos, dd.green.v, 0x00, 0x50, 0x00, 0xFF);
  DebugDraw::drawVector(dd.blue.pos, dd.blue.v, 0x00, 0x00, 0xFF, 0xFF);
  DebugDraw::drawPositionHist(_kinematicStatus.position);
}

void Body::setTarget(const Vec2& target) {
    _kinematicStatusTarget.position = target;
}

void Body::updateKinematic(const float dt, const KinematicSteering& steering) {
    _kinematicStatus.acceleration = steering.acceleration;
    if (_kinematicStatus.acceleration.length() > _maxAcceleration) {
        _kinematicStatus.acceleration = _kinematicStatus.acceleration.normalized() * _maxAcceleration;
    }
    _kinematicStatus.velocity += _kinematicStatus.acceleration * dt;
    if (_kinematicStatus.velocity.length() > _maxSpeed) {
        _kinematicStatus.velocity = _kinematicStatus.velocity.normalized() * _maxSpeed;
    }

    _kinematicStatus.position += _kinematicStatus.velocity * dt;

    _kinematicStatus.rotation += steering.angularAcceleration * dt;
    if (_kinematicStatus.rotation > _maxAngularSpeed) {
        _kinematicStatus.rotation = _maxAngularSpeed;
    }
    _kinematicStatus.orientation += _kinematicStatus.rotation * dt;
}

void Body::update_direct_seek(const float dt) {
    _kinematicStatus.acceleration = {0.0f, 0.0f};
    _kinematicStatus.velocity = (_kinematicStatusTarget.position - _kinematicStatus.position).normalized() * _maxSpeed;

    _steering.acceleration = {0.0f, 0.0f};
    _steering.angularAcceleration = 0.0f;

    updateKinematic(dt, _steering);

    dd.green.pos = _kinematicStatus.position;
    dd.green.v = _kinematicStatus.velocity * 25.0f;

    dd.red.pos = _kinematicStatus.position;
    dd.red.v = {0.0f, 0.0f};

    dd.blue.pos = _kinematicStatus.position;
    dd.blue.v = {0.0f, 0.0f};

}

void Body::update_seek(const float dt) {
    //aceeleration towards the target
    _steering.acceleration = (_kinematicStatusTarget.position - _kinematicStatus.position).normalized() * _maxAcceleration;
    _steering.angularAcceleration = 0.0f; //no angular

    updateKinematic(dt, _steering);

    dd.green.pos = _kinematicStatus.position;
    dd.green.v = _kinematicStatus.velocity * 25.0f;

    dd.blue.pos = _kinematicStatus.position;
    dd.blue.v = _steering.acceleration.normalized() * _maxSpeed * 25.0f;

    dd.red.pos = _kinematicStatus.position + (_kinematicStatus.velocity * 25.0f);
    dd.red.v = dd.blue.v - dd.green.v;
}

void Body::update_direct_flee(const float dt) {
    _kinematicStatus.acceleration = {0.0f, 0.0f};
    _kinematicStatus.velocity = (_kinematicStatus.position - _kinematicStatusTarget.position).normalized() * _maxSpeed;

    _steering.acceleration = {0.0f, 0.0f};
    _steering.angularAcceleration = 0.0f;

    updateKinematic(dt, _steering);

    dd.green.pos = _kinematicStatus.position;
    dd.green.v = _kinematicStatus.velocity * 25.0f;

    dd.red.pos = _kinematicStatus.position;
    dd.red.v = {0.0f, 0.0f};

    dd.blue.pos = _kinematicStatus.position;
    dd.blue.v = {0.0f, 0.0f};
}

void Body::update_flee(const float dt) {
    //aceeleration towards the target
    _steering.acceleration = (_kinematicStatus.position - _kinematicStatusTarget.position).normalized() * _maxAcceleration;
    _steering.angularAcceleration = 0.0f; //no angular

    updateKinematic(dt, _steering);

    dd.green.pos = _kinematicStatus.position;
    dd.green.v = _kinematicStatus.velocity * 25.0f;

    dd.blue.pos = _kinematicStatus.position;
    dd.blue.v = _steering.acceleration.normalized() * _maxSpeed * 25.0f;

    dd.red.pos = _kinematicStatus.position + (_kinematicStatus.velocity * 25.0f);
    dd.red.v = dd.blue.v - dd.green.v;
}

void Body::update_direct_arrive(const float dt) {
    _kinematicStatus.acceleration = {0.0f, 0.0f};

    //direction to the target
    const Vec2 direction = (_kinematicStatusTarget.position - _kinematicStatus.position);
    if (direction.length() < _minDistance) { //inside the radius
        _kinematicStatus.velocity = {0.0f, 0.0f};
    } else {
        _kinematicStatus.velocity = direction.normalized() * direction.length() / _fixedTime;
    }

    _steering.acceleration = {0.0f, 0.0f};
    _steering.angularAcceleration = 0.0f;

    updateKinematic(dt, _steering);


    dd.green.pos = _kinematicStatus.position;
    dd.green.v = _kinematicStatus.velocity * 25.0f;

    dd.red.pos = _kinematicStatus.position;
    dd.red.v = {0.0f, 0.0f};

    dd.blue.pos = _kinematicStatus.position;
    dd.blue.v = {0.0f, 0.0f};
}

void Body::update_arrive(const float dt){
    //direction to the target
    const Vec2 direction = (_kinematicStatusTarget.position - _kinematicStatus.position);
    const float distance = direction.length(); //distance to target

    float speed = _maxSpeed; //max speed
    if (distance < _slowRadius) { //inside the slow zone
        //speed slowing +down
        speed = (_maxSpeed * distance) / _slowRadius;
    }

    //velocity towards the target
    const Vec2 velocity = direction.normalized() * speed;
    //linear acceleration adjusted to time
    _steering.acceleration = (velocity - _kinematicStatus.velocity); // _fixedTime;
    _steering.angularAcceleration = 0.0f;
    printf("_steering.acceleration [%f, %f]\n", _steering.acceleration.x(), _steering.acceleration.y());


    updateKinematic(dt, _steering);

    dd.green.pos = _kinematicStatus.position;
    dd.green.v = _kinematicStatus.velocity * 25.0f;

    dd.red.pos = _kinematicStatus.position;
    dd.red.v = _kinematicStatus.acceleration * 50.0f;

    dd.blue.pos = _kinematicStatus.position;
    dd.blue.v = {0.0f, 0.0f};
}

void Body::update_wandering(const float dt) {
    Vec2 orientation;
    //orientation of character as vector
    orientation.fromPolar(1.0f, _kinematicStatus.orientation);

    _kinematicStatus.velocity = orientation * _maxSpeed; //max speed
    //rotate to random (binomial distribution around 0)
    _kinematicStatus.rotation = _maxRotation * RandomFloat(-1.0f, 1.0f);

    updateKinematic(dt, _steering);

    dd.green.pos = _kinematicStatus.position;
    dd.green.v = _kinematicStatus.velocity * 25.0f;

    dd.red.pos = _kinematicStatus.position;
    dd.red.v = {0.0f, 0.0f};

    dd.blue.pos = _kinematicStatus.position;
    dd.blue.v = {0.0f, 0.0f};
}


