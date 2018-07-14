//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#include "mat3.h"

#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>

namespace MathLib {

#if ML_USE_SSE
#include "../src/mathlib/mat3_sse.cc"
#else
  uint32_t Mat3::mat_size_ = (uint32_t)(sizeof(float) * 9);

#pragma region Constructors
  Mat3::Mat3() {
    memset(matrix_, 0, mat_size_);
  };

  Mat3::Mat3(const Mat3& o) {
    memcpy(matrix_, o.matrix_, mat_size_);
  }

  Mat3::Mat3(const Vec3& c0, const Vec3& c1, const Vec3& c2) {
    matrix_[0] = c0.x();
    matrix_[1] = c0.y();
    matrix_[2] = c0.z();
    matrix_[3] = c1.x();
    matrix_[4] = c1.y();
    matrix_[5] = c1.z();
    matrix_[6] = c2.x();
    matrix_[7] = c2.y();
    matrix_[8] = c2.z();
  }

  Mat3::Mat3(const float o[9]) {
    memcpy(matrix_, o, mat_size_);
  }
#pragma endregion

#pragma region Components
  const Vec3 Mat3::getColumn(unsigned short index) const {
    assert(index<3);
    short int idx = index * 3;
    return Vec3(matrix_[idx], matrix_[idx + 1], matrix_[idx + 2]);
  }

  const Vec3 Mat3::getRow(unsigned short index) const {
    assert(index<3);
    return Vec3(matrix_[index], matrix_[index + 3], matrix_[index + 6]);
  }
#pragma endregion

#pragma region Operators
  Mat3& Mat3::operator=(const Mat3& o) {
    if (this != &o) {
      memcpy(matrix_, o.matrix_, mat_size_);
    }
    return *this;
  }
#pragma endregion

#pragma region Named Operators
  Mat3& Mat3::addEq(const Mat3& o) {
    matrix_[0] += o.matrix_[0];
    matrix_[1] += o.matrix_[1];
    matrix_[2] += o.matrix_[2];
    matrix_[3] += o.matrix_[3];
    matrix_[4] += o.matrix_[4];
    matrix_[5] += o.matrix_[5];
    matrix_[6] += o.matrix_[6];
    matrix_[7] += o.matrix_[7];
    matrix_[8] += o.matrix_[8];
    return *this;
  }

  Mat3& Mat3::subEq(const Mat3& o) {
    matrix_[0] -= o.matrix_[0];
    matrix_[1] -= o.matrix_[1];
    matrix_[2] -= o.matrix_[2];
    matrix_[3] -= o.matrix_[3];
    matrix_[4] -= o.matrix_[4];
    matrix_[5] -= o.matrix_[5];
    matrix_[6] -= o.matrix_[6];
    matrix_[7] -= o.matrix_[7];
    matrix_[8] -= o.matrix_[8];
    return *this;
  }

  Mat3& Mat3::multEq(const Mat3& o) {
    float aux[9];

    aux[0] = (matrix_[0] * o.matrix_[0]) +
      (matrix_[3] * o.matrix_[1]) +
      (matrix_[6] * o.matrix_[2]);
    aux[1] = (matrix_[1] * o.matrix_[0]) +
      (matrix_[4] * o.matrix_[1]) +
      (matrix_[7] * o.matrix_[2]);
    aux[2] = (matrix_[2] * o.matrix_[0]) +
      (matrix_[5] * o.matrix_[1]) +
      (matrix_[8] * o.matrix_[2]);

    aux[3] = (matrix_[0] * o.matrix_[3]) +
      (matrix_[3] * o.matrix_[4]) +
      (matrix_[6] * o.matrix_[5]);
    aux[4] = (matrix_[1] * o.matrix_[3]) +
      (matrix_[4] * o.matrix_[4]) +
      (matrix_[7] * o.matrix_[5]);
    aux[5] = (matrix_[2] * o.matrix_[3]) +
      (matrix_[5] * o.matrix_[4]) +
      (matrix_[8] * o.matrix_[5]);

    aux[6] = (matrix_[0] * o.matrix_[6]) +
      (matrix_[3] * o.matrix_[7]) +
      (matrix_[6] * o.matrix_[8]);
    aux[7] = (matrix_[1] * o.matrix_[6]) +
      (matrix_[4] * o.matrix_[7]) +
      (matrix_[7] * o.matrix_[8]);
    aux[8] = (matrix_[2] * o.matrix_[6]) +
      (matrix_[5] * o.matrix_[7]) +
      (matrix_[8] * o.matrix_[8]);

    memcpy(matrix_, aux, mat_size_);
    return *this;
  }

  Mat3& Mat3::multEq(const float o) {
    matrix_[0] *= o;
    matrix_[1] *= o;
    matrix_[2] *= o;
    matrix_[3] *= o;
    matrix_[4] *= o;
    matrix_[5] *= o;
    matrix_[6] *= o;
    matrix_[7] *= o;
    matrix_[8] *= o;

    return *this;
  }

  Mat3& Mat3::divEq(const float o) {
    assert(o != 0.0f);
    matrix_[0] /= o;
    matrix_[1] /= o;
    matrix_[2] /= o;
    matrix_[3] /= o;
    matrix_[4] /= o;
    matrix_[5] /= o;
    matrix_[6] /= o;
    matrix_[7] /= o;
    matrix_[8] /= o;
    
    return *this;
  }

  const Vec3 Mat3::mult(const Vec3& o) const {
    return Vec3((matrix_[0] * o.x()) + (matrix_[3] * o.y()) + (matrix_[6] * o.z()),
      (matrix_[1] * o.x()) + (matrix_[4] * o.y()) + (matrix_[7] * o.z()),
      (matrix_[2] * o.x()) + (matrix_[5] * o.y()) + (matrix_[8] * o.z()));
  }
#pragma endregion

#pragma region Matrix Ops
  const Mat3 Mat3::transpose() const {
    return Mat3(getRow(0), getRow(1), getRow(2));
  }
#pragma endregion

#pragma region Additional
  void Mat3::zeros() {
    memset(matrix_, 0, mat_size_);
  }
#pragma endregion
#endif

//Common Implementations
  Mat3::~Mat3() {}

#pragma region Operators
  const Vec3 Mat3::operator[](unsigned short index) const {
    assert(index<3);
    return getColumn(index);
  }

  Mat3& Mat3::operator+=(const Mat3& o) {
    return addEq(o);
  }

  Mat3& Mat3::operator-=(const Mat3& o) {
    return subEq(o);
  }

  Mat3& Mat3::operator*=(const Mat3& o) {
    return multEq(o);
  }

  Mat3& Mat3::operator*=(const float o) {
    return multEq(o);
  }

  Mat3& Mat3::operator/=(const float o) {
    assert(o != 0);
    return divEq(o);
  }

  const Mat3 Mat3::operator+(const Mat3& o) const {
    return add(o);
  }

  const Mat3 Mat3::operator-(const Mat3& o) const {
    return sub(o);
  }

  const Mat3 Mat3::operator*(const Mat3& o) const {
    return mult(o);
  }

  const Mat3 Mat3::operator*(const float o) const {
    return mult(o);
  }

  const Mat3 Mat3::operator/(const float o) const {
    assert(o != 0);
    return div(o);
  }

  const Vec3 Mat3::operator*(const Vec3& o) const {
    return mult(o);
  }
#pragma endregion

#pragma region Named Operators
  const Mat3 Mat3::add(const Mat3& o) const {
    Mat3 result = *this;
    result.addEq(o);
    return result;
  }

  const Mat3 Mat3::sub(const Mat3& o) const {
    Mat3 result = *this;
    result.subEq(o);
    return result;
  }

  const Mat3 Mat3::mult(const Mat3& o) const {
    Mat3 result = *this;
    result.multEq(o);
    return result;
  }

  const Mat3 Mat3::mult(const float o) const {
    Mat3 result = *this;
    result.multEq(o);
    return result;
  }

  const Mat3 Mat3::div(const float o) const {
    assert(o != 0.0f);
    Mat3 result = *this;
    result.divEq(o);
    return result;
  }
#pragma endregion

#pragma region Matrix Operations
    const Mat3 Mat3::identity() {
    float id[9] = { 1,0,0,
                    0,1,0,
                    0,0,1 };
    return Mat3(id);
  }
#pragma endregion
}