//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#include "mat4.h"

#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>

namespace MathLib {

#if ML_USE_SSE
#include "../src/mathlib/mat4_sse.cc"
#else
  uint32_t Mat4::mat_size_ = (uint32_t)(sizeof(float) * 16);

#pragma region Constructors
  Mat4::Mat4() {
    memset(matrix_, 0, mat_size_);
  };

  Mat4::Mat4(const Mat4& o) {
    memcpy(matrix_, o.matrix_, mat_size_);
  }

  Mat4::Mat4(const Vec4 &c0, const Vec4 &c1, const Vec4 &c2, const Vec4 &c3) {
    matrix_[0] = c0.x();
    matrix_[1] = c0.y();
    matrix_[2] = c0.z();
    matrix_[3] = c0.w();
    matrix_[4] = c1.x();
    matrix_[5] = c1.y();
    matrix_[6] = c1.z();
    matrix_[7] = c1.w();
    matrix_[8] = c2.x();
    matrix_[9] = c2.y();
    matrix_[10] = c2.z();
    matrix_[11] = c2.w();
    matrix_[12] = c3.x();
    matrix_[13] = c3.y();
    matrix_[14] = c3.z();
    matrix_[15] = c3.w();
  }

  Mat4::Mat4(const float o[16]) {
    memcpy(matrix_, o, mat_size_);
  }
#pragma endregion

#pragma region Components
  const Vec4 Mat4::getColumn(unsigned short index) const {
    assert(index<4);
    short int idx = index * 4;
    return Vec4(matrix_[idx], matrix_[idx + 1], matrix_[idx + 2], matrix_[idx + 3]);
  }

  const Vec4 Mat4::getRow(unsigned short index) const {
    assert(index<4);
    return Vec4(matrix_[index], matrix_[index + 4], matrix_[index + 8], matrix_[index + 12]);
  }
#pragma endregion

#pragma region Operators
  Mat4& Mat4::operator=(const Mat4& o) {
    if (this != &o) {
      memcpy(matrix_, o.matrix_, mat_size_); 
    }
    return *this;
  }
#pragma endregion

#pragma region Named Operators
  Mat4& Mat4::addEq(const Mat4& o) {
    matrix_[0] += o.matrix_[0];
    matrix_[1] += o.matrix_[1];
    matrix_[2] += o.matrix_[2];
    matrix_[3] += o.matrix_[3];
    matrix_[4] += o.matrix_[4];
    matrix_[5] += o.matrix_[5];
    matrix_[6] += o.matrix_[6];
    matrix_[7] += o.matrix_[7];
    matrix_[8] += o.matrix_[8];
    matrix_[9] += o.matrix_[9];
    matrix_[10] += o.matrix_[10];
    matrix_[11] += o.matrix_[11];
    matrix_[12] += o.matrix_[12];
    matrix_[13] += o.matrix_[13];
    matrix_[14] += o.matrix_[14];
    matrix_[15] += o.matrix_[15];
    return *this;
  }

  Mat4& Mat4::subEq(const Mat4& o) {
    matrix_[0] -= o.matrix_[0];
    matrix_[1] -= o.matrix_[1];
    matrix_[2] -= o.matrix_[2];
    matrix_[3] -= o.matrix_[3];
    matrix_[4] -= o.matrix_[4];
    matrix_[5] -= o.matrix_[5];
    matrix_[6] -= o.matrix_[6];
    matrix_[7] -= o.matrix_[7];
    matrix_[8] -= o.matrix_[8];
    matrix_[9] -= o.matrix_[9];
    matrix_[10] -= o.matrix_[10];
    matrix_[11] -= o.matrix_[11];
    matrix_[12] -= o.matrix_[12];
    matrix_[13] -= o.matrix_[13];
    matrix_[14] -= o.matrix_[14];
    matrix_[15] -= o.matrix_[15];
    return *this;
  }

  Mat4& Mat4::multEq(const Mat4& o) {
    float aux[16];

    aux[0] = (matrix_[0] * o.matrix_[0]) + (matrix_[4] * o.matrix_[1]) +
      (matrix_[8] * o.matrix_[2]) + (matrix_[12] * o.matrix_[3]);
    aux[1] = (matrix_[1] * o.matrix_[0]) + (matrix_[5] * o.matrix_[1]) +
      (matrix_[9] * o.matrix_[2]) + (matrix_[13] * o.matrix_[3]);
    aux[2] = (matrix_[2] * o.matrix_[0]) + (matrix_[6] * o.matrix_[1]) +
      (matrix_[10] * o.matrix_[2]) + (matrix_[14] * o.matrix_[3]);
    aux[3] = (matrix_[3] * o.matrix_[0]) + (matrix_[7] * o.matrix_[1]) +
      (matrix_[11] * o.matrix_[2]) + (matrix_[15] * o.matrix_[3]);

    aux[4] = (matrix_[0] * o.matrix_[4]) + (matrix_[4] * o.matrix_[5]) +
      (matrix_[8] * o.matrix_[6]) + (matrix_[12] * o.matrix_[7]);
    aux[5] = (matrix_[1] * o.matrix_[4]) + (matrix_[5] * o.matrix_[5]) +
      (matrix_[9] * o.matrix_[6]) + (matrix_[13] * o.matrix_[7]);
    aux[6] = (matrix_[2] * o.matrix_[4]) + (matrix_[6] * o.matrix_[5]) +
      (matrix_[10] * o.matrix_[6]) + (matrix_[14] * o.matrix_[7]);
    aux[7] = (matrix_[3] * o.matrix_[4]) + (matrix_[7] * o.matrix_[5]) +
      (matrix_[11] * o.matrix_[6]) + (matrix_[15] * o.matrix_[7]);

    aux[8] = (matrix_[0] * o.matrix_[8]) + (matrix_[4] * o.matrix_[9]) +
      (matrix_[8] * o.matrix_[10]) + (matrix_[12] * o.matrix_[11]);
    aux[9] = (matrix_[1] * o.matrix_[8]) + (matrix_[5] * o.matrix_[9]) +
      (matrix_[9] * o.matrix_[10]) + (matrix_[13] * o.matrix_[11]);
    aux[10] = (matrix_[2] * o.matrix_[8]) + (matrix_[6] * o.matrix_[9]) +
      (matrix_[10] * o.matrix_[10]) + (matrix_[14] * o.matrix_[11]);
    aux[11] = (matrix_[3] * o.matrix_[8]) + (matrix_[7] * o.matrix_[9]) +
      (matrix_[11] * o.matrix_[10]) + (matrix_[15] * o.matrix_[11]);

    aux[12] = (matrix_[0] * o.matrix_[12]) + (matrix_[4] * o.matrix_[13]) +
      (matrix_[8] * o.matrix_[14]) + (matrix_[12] * o.matrix_[15]);
    aux[13] = (matrix_[1] * o.matrix_[12]) + (matrix_[5] * o.matrix_[13]) +
      (matrix_[9] * o.matrix_[14]) + (matrix_[13] * o.matrix_[15]);
    aux[14] = (matrix_[2] * o.matrix_[12]) + (matrix_[6] * o.matrix_[13]) +
      (matrix_[10] * o.matrix_[14]) + (matrix_[14] * o.matrix_[15]);
    aux[15] = (matrix_[3] * o.matrix_[12]) + (matrix_[7] * o.matrix_[13]) +
      (matrix_[11] * o.matrix_[14]) + (matrix_[15] * o.matrix_[15]);

    memcpy(matrix_, aux, mat_size_);
    return *this;
  }

  Mat4& Mat4::multEq(const float o) {
    matrix_[0] *= o;
    matrix_[1] *= o;
    matrix_[2] *= o;
    matrix_[3] *= o;
    matrix_[4] *= o;
    matrix_[5] *= o;
    matrix_[6] *= o;
    matrix_[7] *= o;
    matrix_[8] *= o;
    matrix_[9] *= o;
    matrix_[10] *= o;
    matrix_[11] *= o;
    matrix_[12] *= o;
    matrix_[13] *= o;
    matrix_[14] *= o;
    matrix_[15] *= o;
    return *this;
  }

  Mat4& Mat4::divEq(const float o) {
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
    matrix_[9] /= o;
    matrix_[10] /= o;
    matrix_[11] /= o;
    matrix_[12] /= o;
    matrix_[13] /= o;
    matrix_[14] /= o;
    matrix_[15] /= o;
    return *this;
  }

  const Vec4 Mat4::mult(const Vec4& o) const {
    return Vec4((matrix_[0] * o.x()) + (matrix_[4] * o.y()) + (matrix_[8] * o.z()) + (matrix_[12] * o.w()),
      (matrix_[1] * o.x()) + (matrix_[5] * o.y()) + (matrix_[9] * o.z()) + (matrix_[13] * o.w()),
      (matrix_[2] * o.x()) + (matrix_[6] * o.y()) + (matrix_[10] * o.z()) + (matrix_[14] * o.w()),
      (matrix_[3] * o.x()) + (matrix_[7] * o.y()) + (matrix_[11] * o.z()) + (matrix_[15] * o.w()));
  }
#pragma endregion

#pragma region Matrix Ops
  const Mat3 Mat4::to3x3() const {
    float aux[9] = { matrix_[0],matrix_[1],matrix_[2],
      matrix_[4],matrix_[5],matrix_[6],
      matrix_[8],matrix_[9],matrix_[10] };

    return Mat3(aux);
  }

  const Mat4 Mat4::transpose() const {
    return Mat4(getRow(0), getRow(1), getRow(2), getRow(3));
  }

  const Mat4 Mat4::inverse() const {
    float determ = det();

    if (determ != 0) {
      Mat4 res(*this);

      res.matrix_[0] = ((matrix_[5] * matrix_[10] * matrix_[15]) + (matrix_[9] * matrix_[14] * matrix_[7]) + (matrix_[6] * matrix_[11] * matrix_[13]) -
        ((matrix_[7] * matrix_[10] * matrix_[13]) + (matrix_[5] * matrix_[11] * matrix_[14]) + (matrix_[6] * matrix_[9] * matrix_[15]))) / determ;

      res.matrix_[1] = -((matrix_[1] * matrix_[10] * matrix_[15]) + (matrix_[9] * matrix_[14] * matrix_[3]) + (matrix_[2] * matrix_[11] * matrix_[13]) -
        ((matrix_[3] * matrix_[10] * matrix_[13]) + (matrix_[1] * matrix_[11] * matrix_[14]) + (matrix_[2] * matrix_[9] * matrix_[15]))) / determ;

      res.matrix_[2] = ((matrix_[1] * matrix_[6] * matrix_[15]) + (matrix_[3] * matrix_[14] * matrix_[5]) + (matrix_[2] * matrix_[7] * matrix_[13]) -
        ((matrix_[3] * matrix_[6] * matrix_[13]) + (matrix_[1] * matrix_[7] * matrix_[14]) + (matrix_[2] * matrix_[5] * matrix_[15]))) / determ;

      res.matrix_[3] = -((matrix_[1] * matrix_[6] * matrix_[11]) + (matrix_[3] * matrix_[5] * matrix_[10]) + (matrix_[2] * matrix_[7] * matrix_[9]) -
        ((matrix_[3] * matrix_[6] * matrix_[9]) + (matrix_[1] * matrix_[7] * matrix_[10]) + (matrix_[2] * matrix_[5] * matrix_[11]))) / determ;

      res.matrix_[4] = -((matrix_[4] * matrix_[10] * matrix_[15]) + (matrix_[8] * matrix_[14] * matrix_[7]) + (matrix_[6] * matrix_[11] * matrix_[12]) -
        ((matrix_[7] * matrix_[10] * matrix_[12]) + (matrix_[4] * matrix_[11] * matrix_[14]) + (matrix_[6] * matrix_[8] * matrix_[15]))) / determ;

      res.matrix_[5] = ((matrix_[0] * matrix_[10] * matrix_[15]) + (matrix_[8] * matrix_[14] * matrix_[3]) + (matrix_[2] * matrix_[11] * matrix_[12]) -
        ((matrix_[3] * matrix_[10] * matrix_[12]) + (matrix_[0] * matrix_[11] * matrix_[14]) + (matrix_[2] * matrix_[8] * matrix_[15]))) / determ;

      res.matrix_[6] = -((matrix_[0] * matrix_[6] * matrix_[15]) + (matrix_[3] * matrix_[14] * matrix_[4]) + (matrix_[2] * matrix_[7] * matrix_[12]) -
        ((matrix_[3] * matrix_[6] * matrix_[12]) + (matrix_[0] * matrix_[7] * matrix_[14]) + (matrix_[2] * matrix_[4] * matrix_[15]))) / determ;

      res.matrix_[7] = ((matrix_[0] * matrix_[6] * matrix_[11]) + (matrix_[3] * matrix_[4] * matrix_[10]) + (matrix_[2] * matrix_[7] * matrix_[8]) -
        ((matrix_[3] * matrix_[6] * matrix_[8]) + (matrix_[0] * matrix_[7] * matrix_[10]) + (matrix_[2] * matrix_[4] * matrix_[11]))) / determ;

      res.matrix_[8] = ((matrix_[4] * matrix_[9] * matrix_[15]) + (matrix_[8] * matrix_[13] * matrix_[7]) + (matrix_[5] * matrix_[11] * matrix_[12]) -
        ((matrix_[7] * matrix_[9] * matrix_[12]) + (matrix_[4] * matrix_[11] * matrix_[13]) + (matrix_[5] * matrix_[8] * matrix_[15]))) / determ;

      res.matrix_[9] = -((matrix_[0] * matrix_[9] * matrix_[15]) + (matrix_[8] * matrix_[13] * matrix_[3]) + (matrix_[1] * matrix_[11] * matrix_[12]) -
        ((matrix_[3] * matrix_[9] * matrix_[12]) + (matrix_[0] * matrix_[11] * matrix_[13]) + (matrix_[1] * matrix_[8] * matrix_[15]))) / determ;

      res.matrix_[10] = ((matrix_[0] * matrix_[5] * matrix_[15]) + (matrix_[3] * matrix_[4] * matrix_[13]) + (matrix_[1] * matrix_[7] * matrix_[12]) -
        ((matrix_[3] * matrix_[5] * matrix_[12]) + (matrix_[1] * matrix_[4] * matrix_[15]) + (matrix_[0] * matrix_[7] * matrix_[13]))) / determ;

      res.matrix_[11] = -((matrix_[0] * matrix_[5] * matrix_[11]) + (matrix_[3] * matrix_[4] * matrix_[9]) + (matrix_[1] * matrix_[7] * matrix_[8]) -
        ((matrix_[3] * matrix_[5] * matrix_[8]) + (matrix_[0] * matrix_[7] * matrix_[9]) + (matrix_[1] * matrix_[4] * matrix_[11]))) / determ;

      res.matrix_[12] = -((matrix_[4] * matrix_[9] * matrix_[14]) + (matrix_[8] * matrix_[13] * matrix_[6]) + (matrix_[5] * matrix_[10] * matrix_[12]) -
        ((matrix_[6] * matrix_[9] * matrix_[12]) + (matrix_[4] * matrix_[10] * matrix_[13]) + (matrix_[5] * matrix_[8] * matrix_[14]))) / determ;

      res.matrix_[13] = ((matrix_[0] * matrix_[9] * matrix_[14]) + (matrix_[1] * matrix_[10] * matrix_[12]) + (matrix_[2] * matrix_[8] * matrix_[13]) -
        ((matrix_[2] * matrix_[9] * matrix_[12]) + (matrix_[0] * matrix_[10] * matrix_[13]) + (matrix_[1] * matrix_[8] * matrix_[14]))) / determ;

      res.matrix_[14] = -((matrix_[0] * matrix_[5] * matrix_[14]) + (matrix_[1] * matrix_[6] * matrix_[12]) + (matrix_[2] * matrix_[4] * matrix_[13]) -
        ((matrix_[2] * matrix_[5] * matrix_[12]) + (matrix_[1] * matrix_[4] * matrix_[14]) + (matrix_[0] * matrix_[6] * matrix_[13]))) / determ;

      res.matrix_[15] = ((matrix_[0] * matrix_[5] * matrix_[10]) + (matrix_[1] * matrix_[6] * matrix_[8]) + (matrix_[2] * matrix_[4] * matrix_[9]) -
        ((matrix_[2] * matrix_[5] * matrix_[8]) + (matrix_[0] * matrix_[6] * matrix_[9]) + (matrix_[1] * matrix_[4] * matrix_[10]))) / determ;

      return res;
    } else return Mat4();     //returns empty matrix
  }

  const float Mat4::det() const {
    float adj1 = matrix_[0] *
      ((matrix_[5] * matrix_[10] * matrix_[15]) + (matrix_[9] * matrix_[14] * matrix_[7]) + (matrix_[6] * matrix_[11] * matrix_[13]) -
      ((matrix_[7] * matrix_[10] * matrix_[13]) + (matrix_[5] * matrix_[11] * matrix_[14]) + (matrix_[6] * matrix_[9] * matrix_[15])));

    float adj2 = matrix_[4] *
      ((matrix_[1] * matrix_[10] * matrix_[15]) + (matrix_[9] * matrix_[14] * matrix_[3]) + (matrix_[2] * matrix_[11] * matrix_[13]) -
      ((matrix_[3] * matrix_[10] * matrix_[13]) + (matrix_[1] * matrix_[11] * matrix_[14]) + (matrix_[2] * matrix_[9] * matrix_[15])));

    float adj3 = matrix_[8] *
      ((matrix_[1] * matrix_[6] * matrix_[15]) + (matrix_[3] * matrix_[14] * matrix_[5]) + (matrix_[2] * matrix_[7] * matrix_[13]) -
      ((matrix_[3] * matrix_[6] * matrix_[13]) + (matrix_[1] * matrix_[7] * matrix_[14]) + (matrix_[2] * matrix_[5] * matrix_[15])));

    float adj4 = matrix_[12] *
      ((matrix_[1] * matrix_[6] * matrix_[11]) + (matrix_[3] * matrix_[5] * matrix_[10]) + (matrix_[2] * matrix_[7] * matrix_[9]) -
      ((matrix_[3] * matrix_[6] * matrix_[9]) + (matrix_[1] * matrix_[7] * matrix_[10]) + (matrix_[2] * matrix_[5] * matrix_[11])));

    return adj1 - adj2 + adj3 - adj4;
  }
#pragma endregion

#pragma region Additional
  void Mat4::zeros() {          
    memset(matrix_, 0, mat_size_);
  }
#pragma endregion
#endif

//Common Implementations
  Mat4::~Mat4() {}

#pragma region Operators
  const Vec4 Mat4::operator[](unsigned short index) const {
    assert(index<4);
    return getColumn(index);
  }

  Mat4& Mat4::operator+=(const Mat4& o) {
    return addEq(o);
  }

  Mat4& Mat4::operator-=(const Mat4& o) {
    return subEq(o);
  }

  Mat4& Mat4::operator*=(const Mat4& o) {
    return multEq(o);
  }

  Mat4& Mat4::operator*=(const float o) {
    return multEq(o);
  }

  Mat4& Mat4::operator/=(const float o) {
    assert(o != 0.0f);
    return divEq(o);
  }

  const Mat4 Mat4::operator+(const Mat4& o) const {
    return add(o);
  }

  const Mat4 Mat4::operator-(const Mat4& o) const {
    return sub(o);
  }

  const Mat4 Mat4::operator*(const Mat4& o) const {
    return mult(o);
  }

  const Mat4 Mat4::operator*(const float o) const {
    return mult(o);
  }

  const Mat4 Mat4::operator/(const float o) const {
    assert(o != 0);
    return div(o);
  }

  const Vec4 Mat4::operator*(const Vec4& o) const {
    return mult(o);
  }

  const Vec3 Mat4::operator*(const Vec3& o) const {
    return mult(o);
  }
#pragma endregion

#pragma region Named Operators
  const Mat4 Mat4::add(const Mat4& o) const {
    Mat4 result = *this;
    result.addEq(o);
    return result;
  }

  const Mat4 Mat4::sub(const Mat4& o) const {
    Mat4 result = *this;
    result.subEq(o);
    return result;
  }

  const Mat4 Mat4::mult(const Mat4& o) const {
    Mat4 result = *this;
    result.multEq(o);
    return result;
  }

  const Mat4 Mat4::mult(const float o) const {
    Mat4 result = *this;
    result.multEq(o);
    return result;
  }

  const Mat4 Mat4::div(const float o) const {
    assert(o != 0.0f);
    Mat4 result = *this;
    result.divEq(o);
    return result;
  }

  const Vec3 Mat4::mult(const Vec3& o) const {
    return Vec3(to3x3().mult(o));
  }
#pragma endregion

#pragma region Matrix Operations
  const Mat4 Mat4::identity() {
    float id[16] = { 1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1 };
    return Mat4(id);
  }
#pragma endregion
}