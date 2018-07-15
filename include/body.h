//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __BODY_H__
#define __BODY_H__ 1

#include <sprite.h>
#include <defines.h>
#include <mathlib/vec2.h>
using MathLib::Vec2;

class Body {
  public:

    struct KinematicStatus {
        Vec2 position { 0.0f, 0.0f };
        float orientation;
        Vec2 velocity { 0.0f, 0.0f }; //linear velocity
        float rotation; //angular velocity
        Vec2 acceleration { 0.0f, 0.0f }; //linear acceleration
    };

    struct KinematicSteering {
        Vec2 acceleration { 0.0f, 0.0f }; //linear velocity
        float angularAcceleration; //angular velocity
    };

    enum class Type {
      Green,
      Blue,
      Purple,
    };

    enum class SteeringMode {
        Direct_Seek,
        Seek,
        Direct_Flee,
        Flee,
        Direct_Arrive,
        Arrive
    };

    Body() {};
    ~Body() {};

    void init(const Type type);
    void update(const float dt);
    void render() const;

    void setTarget(const Vec2& target);
    void setSteering(const SteeringMode steering) { steering_ = steering; };
  private:
    void updateKinematic(const float dt, const KinematicSteering& steering);

    void update_direct_seek(const float dt);
    void update_seek(const float dt);
    void update_direct_flee(const float dt);
    void update_flee(const float dt);
    void update_direct_arrive(const float dt);
    void update_arrive(const float dt);

    Sprite sprite_;
    Type type_;
    SteeringMode steering_;

    KinematicStatus _kinematicStatus;
    KinematicSteering _steering;
    const float _maxSpeed { 5.f };
    const float _maxAcceleration { 1.0f};
    const float _maxAngularSpeed = { 1.0f };

    const float _minDistance { 5.0f }; //squared radius
    const float _fixedTime { 50.f };


    KinematicStatus _kinematicStatusTarget;

    const float slow_radius_ { 100.0f };

    struct {
      struct {
        Vec2 pos;
        Vec2 v;
      } green, red, blue;
    } dd;
};

#endif
