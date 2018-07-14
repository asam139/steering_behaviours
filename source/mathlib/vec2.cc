//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include "vec2.h"

#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>

namespace MathLib {
#if ML_USE_SSE

#include "../src/mathlib/vec2_sse.cc"

#else
  uint32_t Vec2::vec_size_ = (uint32_t)(sizeof(float) * 2);

#pragma region Constructors
  Vec2::Vec2() {
    memset(vec_, 0, vec_size_);
}

  Vec2::Vec2(const Vec2& o) {
    memcpy(vec_, o.vec_, vec_size_);
  }

  Vec2::Vec2(const float u1, const float u2) {
    vec_[X] = u1;
    vec_[Y] = u2;
  }
#pragma endregion

#pragma region Components
  const float Vec2::x() const {
    return vec_[X];
  }

  float& Vec2::x() {
    return vec_[X];
  }

  const float Vec2::y() const {
    return vec_[Y];
  }

  float& Vec2::y() {
    return vec_[Y];
  }
#pragma endregion

#pragma region Operators
  Vec2& Vec2::operator=(const Vec2& o) {
    if (this != &o) {
      memcpy(vec_, o.vec_, vec_size_);
    }
    return *this;
  }

  const float Vec2::operator[](uint16_t index) const {  // subscript without modifying
    assert(index<2);
    return vec_[index];
  }

  float& Vec2::operator[](uint16_t index) {  // Subscript modifying
    assert(index<2);
    return vec_[index];
  }

  const Vec2 Vec2::operator-() const {
    return Vec2(-vec_[X], -vec_[Y]);
  }
#pragma endregion

#pragma region Named Operators
  Vec2& Vec2::addEq(const Vec2& o) {
    vec_[X] += o.x();
    vec_[Y] += o.y();
    return *this;
  }

  Vec2& Vec2::subEq(const Vec2& o) {
    vec_[X] -= o.x();
    vec_[Y] -= o.y();
    return *this;
  }

  Vec2& Vec2::multEq(const float o) {
    vec_[X] *= o;
    vec_[Y] *= o;
    return *this;
  }

  Vec2& Vec2::divEq(const float o) {
    assert(o != 0.0f);
    vec_[X] /= o;
    vec_[Y] /= o;
    return *this;
  }
#pragma endregion

#pragma region Vector Ops
  float Vec2::dot(const Vec2& o) const {
    return (vec_[X] * o.x()) + (vec_[Y] * o.y());
  }

  float Vec2::length() const {
    return (float)sqrt((double)dot(*this));
  }

  const Vec2 Vec2::normalized() const {
    float module = length();
    assert(module != 0);
    return Vec2(vec_[X] / module, vec_[Y] / module);
  }
#pragma endregion

#pragma region Additional
  void Vec2::zeros() {
    memset(vec_, 0, vec_size_);
  }

  void Vec2::fromPolar(const float dist, const float ang, const bool use_rads) {
    float rad = ang;
    if (!use_rads) {
      rad *= (float)(M_PI / 180);
    }
    vec_[0] = dist*cos(rad);
    vec_[1] = dist*sin(rad);
  }
#pragma endregion
#endif

//Common Implementations

  Vec2::~Vec2() {}

#pragma region Operators
  Vec2& Vec2::operator+=(const Vec2& o) {
    return addEq(o);
  }

  Vec2& Vec2::operator-=(const Vec2& o) {
    return subEq(o);
  }

  Vec2& Vec2::operator*=(const float o) {
    return multEq(o);
  }

  Vec2& Vec2::operator/=(const float o) {
    assert(o != 0);
    return divEq(o);
  }

  const Vec2 Vec2::operator+(const Vec2& o) const {
    return add(o);
  }

  const Vec2 Vec2::operator-(const Vec2& o) const {
    return sub(o);
  }

  const Vec2 Vec2::operator*(const float o) const {
    return mult(o);
  }

  const Vec2 Vec2::operator/(const float o) const {
    assert(o != 0);
    return div(o);
  }

  float Vec2::operator*(const Vec2& o) const {
    return dot(o);
  }

  inline const bool Vec2::operator==(Vec2 &o) {
    return !(*this != o);
  }

  inline const bool Vec2::operator!=(Vec2 &o) {
    return ((x() == o.x()) && (y() == o.y())) ? true : false;
  }
#pragma endregion

#pragma region Named Operators
  const Vec2 Vec2::add(const Vec2& o) const {
    Vec2 result = *this;
    result.addEq(o);
    return result;
  }

  const Vec2 Vec2::sub(const Vec2& o) const {
    Vec2 result = *this;
    result.subEq(o);
    return result;
  }

  const Vec2 Vec2::mult(const float o) const {
    Vec2 result = *this;
    result.multEq(o);
    return result;
  }

  const Vec2 Vec2::div(const float o) const {
    assert(o != 0.0f);
    Vec2 result = *this;
    result.divEq(o);
    return result;
  }
#pragma endregion

#pragma region Vector Ops
  float Vec2::length2() const {
    return dot(*this);
  }

  const Vec2 Vec2::tangent() const {
    return Vec2(-y(), x());
  }

  const Vec2 Vec2::trunc(const float o) const {
    float l = length();
    if (l > o) {
      return normalized() * o;
    } else {
      return *this;
    }
  }
#pragma endregion

#pragma region Additional
  void Vec2::toPolar(float &dist, float &ang, const bool use_rads) const {
    dist = length();
    ang = atan(y() / x());
    if (!use_rads) {
      ang *= (float)(180 / M_PI);
    }
  }
#pragma endregion

  std::ostream& operator<<(std::ostream& left, const Vec2& v) {
    left << "(" << v.x() << "," << v.y() << ")";
    return left;
  }
}