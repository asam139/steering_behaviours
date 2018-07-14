//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#include "vec4.h"

#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>

namespace MathLib {
#if ML_USE_SSE
#include "../src/mathlib/vec4_sse.cc"
#else
  uint32_t Vec4::vec_size_ = (uint32_t)(sizeof(float) * 4);

#pragma region Constructors
  Vec4::Vec4() {
    memset(vec_, 0, vec_size_);
  };

  Vec4::Vec4(const Vec4& o) {
    memcpy(vec_, o.vec_, vec_size_);
  }

  Vec4::Vec4(const Vec3& o, const float u4) {
    vec_[X] = o.x();
    vec_[Y] = o.y();
    vec_[Z] = o.z();
    vec_[W] = u4;
  }

  Vec4::Vec4(const float u1, const float u2, const float u3, const float u4) {
    vec_[X] = u1;
    vec_[Y] = u2;
    vec_[Z] = u3;
    vec_[W] = u4;
  }
#pragma endregion

#pragma region Components
  const float Vec4::x() const {
    return vec_[X];
  }

  float& Vec4::x() {
    return vec_[X];
  }

  const float Vec4::y() const {
    return vec_[Y];
  }

  float& Vec4::y() {
    return vec_[Y];
  }

  const float Vec4::z() const {
    return vec_[Z];
  }

  float& Vec4::z() {
    return vec_[Z];
  }

  const float Vec4::w() const {
    return vec_[W];
  }

  float& Vec4::w() {
    return vec_[W];
  }
#pragma endregion

#pragma region Operators
  Vec4& Vec4::operator=(const Vec4& o) {
    if (this != &o) {
      memcpy(vec_, o.vec_, vec_size_);
    }
    return *this;
  }

  const float Vec4::operator[](unsigned short index) const {
    assert(index<4);
    return vec_[index];
  }

  float& Vec4::operator[](unsigned short index) {
    assert(index<4);
    return vec_[index];
  }

  const Vec4 Vec4::operator-() const {
    return Vec4(-vec_[X], -vec_[Y], -vec_[Z], -vec_[W]);
  }
#pragma endregion

#pragma region Named Operators
  Vec4& Vec4::addEq(const Vec4& o) {
    vec_[X] += o.x();
    vec_[Y] += o.y();
    vec_[Z] += o.z();
    vec_[W] += o.w();
    return *this;
  }

  Vec4& Vec4::subEq(const Vec4& o) {
    vec_[X] -= o.x();
    vec_[Y] -= o.y();
    vec_[Z] -= o.z();
    vec_[W] -= o.w();
    return *this;
  }

  Vec4& Vec4::multEq(const float o) {
    vec_[X] *= o;
    vec_[Y] *= o;
    vec_[Z] *= o;
    vec_[W] *= o;
    return *this;
  }

  Vec4& Vec4::divEq(const float o) {
    assert(o != 0.0f);
    vec_[X] /= o;
    vec_[Y] /= o;
    vec_[Z] /= o;
    vec_[W] /= o;
    return *this;
  }
#pragma endregion

#pragma region Vector Ops
  float Vec4::dot(const Vec4& o) const {
    return (vec_[X] * o.x()) + (vec_[Y] * o.y()) + (vec_[Z] * o.z()) + (vec_[W] * o.w());
  }

  float Vec4::length() const {
    return (float)sqrt((double)dot(*this));
  }

  const Vec4 Vec4::normalized() const {
    float module = length();
    assert(module != 0);
    return Vec4(vec_[X] / module, vec_[Y] / module, vec_[Z] / module, vec_[W] / module);
  }
#pragma endregion

#pragma region Additional
  void Vec4::zeros() {
    memset(vec_, 0, vec_size_);
  }
#pragma endregion
#endif

//Common Implementations
  Vec4::~Vec4() {}

#pragma region Operators
  Vec4& Vec4::operator+=(const Vec4& o) {
    return addEq(o);
  }

  Vec4& Vec4::operator-=(const Vec4& o) {
    return subEq(o);
  }

  Vec4& Vec4::operator*=(const float o) {
    return multEq(o);
  }

  Vec4& Vec4::operator/=(const float o) {
    assert(o != 0);
    return divEq(o);
  }

  const Vec4 Vec4::operator+(const Vec4& o) const {
    return add(o);
  }

  const Vec4 Vec4::operator-(const Vec4& o) const {
    return sub(o);
  }

  const Vec4 Vec4::operator*(const float o) const {
    return mult(o);
  }

  const Vec4 Vec4::operator/(const float o) const {
    assert(o != 0);
    return div(o);
  }

  float Vec4::operator*(const Vec4& o) const {
    return dot(o);
  }

  inline const bool Vec4::operator==(Vec4 &o) {
    return !(*this != o);
  }

  inline const bool Vec4::operator!=(Vec4 &o) {
    return ((x() == o.x()) && (y() == o.y()) && (z() == o.z())) ? true : false;
  }
#pragma endregion

#pragma region Named Operators
  const Vec4 Vec4::add(const Vec4& o) const {
    Vec4 result = *this;
    result.addEq(o);
    return result;
  }

  const Vec4 Vec4::sub(const Vec4& o) const {
    Vec4 result = *this;
    result.subEq(o);
    return result;
  }

  const Vec4 Vec4::mult(const float o) const {
    Vec4 result = *this;
    result.multEq(o);
    return result;
  }

  const Vec4 Vec4::div(const float o) const {
    assert(o != 0.0f);
    Vec4 result = *this;
    result.divEq(o);
    return result;
  }
#pragma endregion

#pragma region Vector Ops
  float Vec4::length2() const {
    return dot(*this);
  }
#pragma endregion

  std::ostream& operator<<(std::ostream& left, const Vec4& v) {
    left << "(" << v.x() << "," << v.y() << "," << v.z() << "," << v.w() << ")";
    return left;
  }

}