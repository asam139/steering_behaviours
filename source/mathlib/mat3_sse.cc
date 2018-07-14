//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#include "vec4.h"
#include "mat4.h"

#pragma region Constructors
  Mat3::Mat3() {
    matrix_[0] = _mm_setzero_ps();
    matrix_[1] = _mm_setzero_ps();
    matrix_[2] = _mm_setzero_ps();
  }

  Mat3::Mat3(const Mat3& o) {
    matrix_[0] = o.matrix_[0];
    matrix_[1] = o.matrix_[1];
    matrix_[2] = o.matrix_[2];
  }

  Mat3::Mat3(const Vec3 &c0, const Vec3 &c1, const Vec3 &c2) {
    matrix_[0] = c0.sse_val();
    matrix_[1] = c1.sse_val();
    matrix_[2] = c2.sse_val();
  }

  Mat3::Mat3(const float o[9]) {
    matrix_[0] = _mm_set_ps(0.0f, o[2], o[1], o[0]);
    matrix_[1] = _mm_set_ps(0.0f, o[5], o[4], o[3]);
    matrix_[2] = _mm_set_ps(0.0f, o[8], o[7], o[6]);
  }
#pragma endregion

#pragma region Components
  const Vec3 Mat3::getColumn(unsigned short index) const {
    assert(index<3);
    return Vec3(matrix_[index]);
  }

  const Vec3 Mat3::getRow(unsigned short index) const {
    assert(index<3);
    return Vec3(matrix_[0].m128_f32[index], matrix_[1].m128_f32[index], matrix_[2].m128_f32[index]);
  }

  const __m128 Mat3::getRow_sse(unsigned short index) const {
    assert(index < 3);
    return _mm_set_ps(0.0f, matrix_[0].m128_f32[index], matrix_[1].m128_f32[index], matrix_[2].m128_f32[index]);
  }
#pragma endregion

#pragma region Operators
  Mat3& Mat3::operator=(const Mat3& o) {
    if (this != &o) {
      matrix_[0] = o.matrix_[0];
      matrix_[1] = o.matrix_[1];
      matrix_[2] = o.matrix_[2];
    }
    return *this;
  }
#pragma endregion

#pragma region Named Operators
  Mat3& Mat3::addEq(const Mat3& o) {
    matrix_[0] = _mm_add_ps(matrix_[0], o.matrix_[0]);
    matrix_[1] = _mm_add_ps(matrix_[1], o.matrix_[1]);
    matrix_[2] = _mm_add_ps(matrix_[2], o.matrix_[2]);
    return *this;
  }

  Mat3& Mat3::subEq(const Mat3& o) {
    matrix_[0] = _mm_sub_ps(matrix_[0], o.matrix_[0]);
    matrix_[1] = _mm_sub_ps(matrix_[1], o.matrix_[1]);
    matrix_[2] = _mm_sub_ps(matrix_[2], o.matrix_[2]);
    return *this;
  }

  Mat3& Mat3::multEq(const Mat3& o) {            
    __m128 r0, r1, r2;
    __m128 m0 = _mm_set1_ps(0.0f);

    r0 = _mm_add_ps(_mm_add_ps( _mm_mul_ps(matrix_[0], _mm_shuffle_ps(o.matrix_[0], o.matrix_[0], _MM_SHUFFLE(0, 0, 0, 0))),  //Element x Column
                                _mm_mul_ps(matrix_[1], _mm_shuffle_ps(o.matrix_[0], o.matrix_[0], _MM_SHUFFLE(1, 1, 1, 1)))),
                    _mm_add_ps( _mm_mul_ps(matrix_[2], _mm_shuffle_ps(o.matrix_[0], o.matrix_[0], _MM_SHUFFLE(2, 2, 2, 2))),
                                m0));

    r1 = _mm_add_ps(_mm_add_ps( _mm_mul_ps(matrix_[0], _mm_shuffle_ps(o.matrix_[1], o.matrix_[1], _MM_SHUFFLE(0, 0, 0, 0))),
                                _mm_mul_ps(matrix_[1], _mm_shuffle_ps(o.matrix_[1], o.matrix_[1], _MM_SHUFFLE(1, 1, 1, 1)))),
                    _mm_add_ps( _mm_mul_ps(matrix_[2], _mm_shuffle_ps(o.matrix_[1], o.matrix_[1], _MM_SHUFFLE(2, 2, 2, 2))),
                                m0));

    r2 = _mm_add_ps(_mm_add_ps( _mm_mul_ps(matrix_[0], _mm_shuffle_ps(o.matrix_[2], o.matrix_[2], _MM_SHUFFLE(0, 0, 0, 0))),
                                _mm_mul_ps(matrix_[1], _mm_shuffle_ps(o.matrix_[2], o.matrix_[2], _MM_SHUFFLE(1, 1, 1, 1)))),
                    _mm_add_ps( _mm_mul_ps(matrix_[2], _mm_shuffle_ps(o.matrix_[2], o.matrix_[2], _MM_SHUFFLE(2, 2, 2, 2))),
                                m0));
    matrix_[0] = r0;
    matrix_[1] = r1;
    matrix_[2] = r2;
    return *this;
  }

  Mat3& Mat3::multEq(const float o) {
    __m128 aux = _mm_set1_ps(o);
    matrix_[0] = _mm_mul_ps(matrix_[0], aux);
    matrix_[1] = _mm_mul_ps(matrix_[1], aux);
    matrix_[2] = _mm_mul_ps(matrix_[2], aux);
    return *this;
  }

  Mat3& Mat3::divEq(const float o) {
    assert(o != 0.0f);
    __m128 aux = _mm_set1_ps(o);
    matrix_[0] = _mm_div_ps(matrix_[0], aux);
    matrix_[1] = _mm_div_ps(matrix_[1], aux);
    matrix_[2] = _mm_div_ps(matrix_[2], aux);
    return *this;
  }

  const Vec3 Mat3::mult(const Vec3& o) const {    
    __m128 vec = o.sse_val();
    __m128 m0 = _mm_set1_ps(0.0f);
    return Vec3(_mm_hadd_ps(_mm_hadd_ps(_mm_mul_ps(getRow_sse(0), vec), _mm_mul_ps(getRow_sse(1), vec)),    //Row x Vector
                            _mm_hadd_ps(_mm_mul_ps(getRow_sse(2), vec), m0)));
  }
#pragma endregion

#pragma region Matrix Ops
  const Mat3 Mat3::transpose() const {
    Mat3 aux(*this);
    __m128 m0 = _mm_set1_ps(0.0f);
    _MM_TRANSPOSE4_PS(aux.matrix_[0], aux.matrix_[1], aux.matrix_[2], m0);
    return aux;
  }
#pragma endregion

#pragma region Additional
  void Mat3::zeros() {
    matrix_[0] = _mm_setzero_ps();
    matrix_[1] = _mm_setzero_ps();
    matrix_[2] = _mm_setzero_ps();
  }
#pragma endregion