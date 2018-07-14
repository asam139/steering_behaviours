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
    enum class Type {
      Green,
      Blue,
      Purple,
    };

    enum class Steering {
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
    void update(const uint32_t dt);
    void render() const;

    void setTarget(const Vec2& target);
    void setSteering(const Steering steering) { steering_ = steering; };
  private:
    void update_direct_seek(const uint32_t);
    void update_seek(const uint32_t);
    void update_direct_flee(const uint32_t dt);
    void update_flee(const uint32_t dt);
    void update_direct_arrive(const uint32_t dt);
    void update_arrive(const uint32_t dt);

    Sprite sprite_;
    Type type_;
    Steering steering_;

    Vec2 target_ { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
    Vec2 position_ { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

    Vec2 velocity_{ 0.0f, 0.0f };
    float mass_ = 1.0f;
    float rotation_ = 0.0f;

    const float max_velocity_ { 5.f };
    const float max_steering_ { 0.1f };

    const float sq_radius_ { 5.0f }; //squared radius
    const float time_to_target_ { 1.f };

    struct {
      struct {
        Vec2 pos;
        Vec2 v;
      } green, red, blue;
    } dd;
};

#endif
