//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#include "vec3.h"

#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>

namespace MathLib {

#if ML_USE_SSE
#include "../src/mathlib/vec3_sse.cc"

#else
  uint32_t Vec3::vec_size_ = (uint32_t)(sizeof(float) * 3);

#pragma region Constructors
  Vec3::Vec3() {
    memset(vec_, 0, vec_size_);
  };

  Vec3::Vec3(const Vec3& o) {
    memcpy(vec_, o.vec_, vec_size_);
  }

  Vec3::Vec3(const float u1, const float u2, const float u3) {
    vec_[X] = u1;
    vec_[Y] = u2;
    vec_[Z] = u3;
  }
#pragma endregion

#pragma region Components
  const float Vec3::x() const {
    return vec_[X]; 
  }

  float& Vec3::x() {
    return vec_[X];
  }

  const float Vec3::y() const {
    return vec_[Y];
  }

  float& Vec3::y() {
    return vec_[Y];
  }

  const float Vec3::z() const {
    return vec_[Z];
  }

  float& Vec3::z() {
    return vec_[Z];
  }
#pragma endregion

#pragma region Operators
  Vec3& Vec3::operator=(const Vec3& o) {
    if (this != &o) {
      memcpy(vec_, o.vec_, vec_size_);
    }
    return *this;
  }

  const float Vec3::operator[](unsigned short index) const { 
    assert(index<3);
    return vec_[index];
  }

  float& Vec3::operator[](unsigned short index) {
    assert(index<3);
    return vec_[index];
  }

  const Vec3 Vec3::operator-() const {
    return Vec3(-vec_[X], -vec_[Y], -vec_[Z]);
  }
#pragma endregion

#pragma region Named Operators
  Vec3& Vec3::addEq(const Vec3& o) {
    vec_[X] += o.x();
    vec_[Y] += o.y();
    vec_[Z] += o.z();
    return *this;
  }

  Vec3& Vec3::subEq(const Vec3& o) {
    vec_[X] -= o.x();
    vec_[Y] -= o.y();
    vec_[Z] -= o.z();
    return *this;
  }

  Vec3& Vec3::multEq(const float o) {
    vec_[X] *= o;
    vec_[Y] *= o;
    vec_[Z] *= o;
    return *this;
  }

  Vec3& Vec3::divEq(const float o) {
    assert(o != 0.0f);
    vec_[X] /= o;
    vec_[Y] /= o;
    vec_[Z] /= o;
    return *this;
  }
#pragma endregion

#pragma region Vector Ops
  float Vec3::dot(const Vec3& o) const {
    return (vec_[X] * o.x()) + (vec_[Y] * o.y()) + (vec_[Z] * o.z());
  }

  float Vec3::length() const {
    return (float)sqrt((double)dot(*this));
  }

  const Vec3 Vec3::normalized() const {
    float module = length();
    assert(module != 0);
    return Vec3(vec_[X] / module, vec_[Y] / module, vec_[Z] / module);
  }

  const Vec3 Vec3::cross(const Vec3& o) const {
    return Vec3(vec_[Y] * o.z() - vec_[Z] * o.y(), vec_[Z] * o.x() - vec_[X] * o.z(), vec_[X] * o.y() - vec_[Y] * o.x());
  }
#pragma endregion

#pragma region Additional
  void Vec3::zeros() {
    memset(vec_, 0, vec_size_);
  }
#pragma endregion
#endif

//Common Implementations
  Vec3::~Vec3() {}

#pragma region Operators
  Vec3& Vec3::operator+=(const Vec3& o) {
    return addEq(o);
  }

  Vec3& Vec3::operator-=(const Vec3& o) {
    return subEq(o);
  }

  Vec3& Vec3::operator*=(const float o) {
    return multEq(o);
  }

  Vec3& Vec3::operator/=(const float o) {
    assert(o != 0);
    return divEq(o);
  }

  const Vec3 Vec3::operator+(const Vec3& o) const {
    return add(o);
  }

  const Vec3 Vec3::operator-(const Vec3& o) const {
    return sub(o);
  }

  const Vec3 Vec3::operator^(const Vec3& o) const {
    return cross(o);
  }

  const Vec3 Vec3::operator*(const float o) const {
    return mult(o);
  }

  const Vec3 Vec3::operator/(const float o) const {
    assert(o != 0);
    return div(o);
  }

  float Vec3::operator*(const Vec3& o) const {
    return dot(o);
  }

  inline const bool Vec3::operator==(Vec3 &o) {
    return !(*this != o);
  }

  inline const bool Vec3::operator!=(Vec3 &o) {
    return ((x() == o.x()) && (y() == o.y()) && (z() == o.z())) ? true : false;
  }
#pragma endregion

#pragma region Named Operators
  const Vec3 Vec3::add(const Vec3& o) const {
    Vec3 result = *this;
    result.addEq(o);
    return result;
  }

  const Vec3 Vec3::sub(const Vec3& o) const {
    Vec3 result = *this;
    result.subEq(o);
    return result;
  }

  const Vec3 Vec3::mult(const float o) const {
    Vec3 result = *this;
    result.multEq(o);
    return result;
  }

  const Vec3 Vec3::div(const float o) const {
    assert(o != 0.0f);
    Vec3 result = *this;
    result.divEq(o);
    return result;
  }
#pragma endregion

#pragma region Vector Ops
  float Vec3::length2() const {
    return dot(*this);
  }
#pragma endregion

  std::ostream& operator<<(std::ostream& left, const Vec3& v) {
    left << "(" << v.x() << "," << v.y() << "," << v.z() << ")";
    return left;
  }
}