//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#ifndef __ML_MAT4_H__
#define __ML_MAT4_H__ 1

#include "defines.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"

#include <iostream>

#if ML_USE_SSE
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>      //TODO Untested SSE outside MSCV
#endif  
#endif

namespace MathLib {

  class Mat4 {
  public:
    /** Default constructor. Sets to zeros */
    Mat4();

    /** Copy constructor
    @param o Matrix to copy from */
    Mat4(const Mat4& o);

    /** Constructor from four vec4 columns*/
    Mat4(const Vec4& c0, const Vec4& c1, const Vec4& c2, const Vec4& c3);

    /** Constructor from a 16-position float array */
    Mat4(const float o[16]);

    /** Destructor */
    ~Mat4();

    /** Assignment operator
    @param o Matrix to copy from */
    Mat4& operator=(const Mat4& o);

    /** Returns a column, the same as getColumn(idx) */
    const Vec4 operator[](unsigned short index) const;

    /** Returns a column */
    const Vec4 getColumn(unsigned short index) const;

    /** Returns a row */
    const Vec4 getRow(unsigned short index) const;

    /** Returns a row SSE */
#if ML_USE_SSE
    const __m128 getRow_sse(unsigned short index) const;
#endif

    /** Internal addition operator */
    Mat4& operator+=(const Mat4& o);
    /* Internal substraction operator */
    Mat4& operator-=(const Mat4& o);
    /** Internal multiplication operator */
    Mat4& operator*=(const Mat4& o);
    /** Internal scalar multiplication */
    Mat4& operator*=(float o);
    /** Internal scalar division */
    Mat4& operator/=(float o);

    /** External addition */
    const Mat4 operator+(const Mat4& o) const;
    /** External substraction */
    const Mat4 operator-(const Mat4& o) const;
    /** External multiplication */
    const Mat4 operator*(const Mat4& o) const;
    /** External scalar multiplication */
    const Mat4 operator*(float o) const;
    /** External scalar division */
    const Mat4 operator/(float o) const;

    /** Vector multiplication by vec4 */
    const Vec4 operator*(const Vec4 & o) const;
    /** Vector multiplication by vec3 */
    const Vec3 operator*(const Vec3 & o) const;

    /** Return a 3x3 Matrix version of this one */
    const Mat3 to3x3() const;

    /** Transpose Matrix */
    const Mat4 transpose() const;

    /** Returns inverse Matrix */
    const Mat4 inverse() const;

    /** Load identity Matrix */
    static const Mat4 identity();

    /** Determinant of Matrix */
    const float det() const;

    /* Named methods */
    /** Internal addition */
    Mat4& addEq(const Mat4& o);
    /** Internal substraction */
    Mat4& subEq(const Mat4& o);
    /** Internal mutiplication */
    Mat4& multEq(const Mat4& o);
    /** Internal scalar mutiplication */
    Mat4& multEq(const float o);
    /** Internal scalar division */
    Mat4& divEq(const float o);
    /** External addition */
    const Mat4 add(const Mat4& o) const;
    /** External substraction */
    const Mat4 sub(const Mat4& o) const;
    /** External multiplication */
    const Mat4 mult(const Mat4& o) const;
    /** External scalar multiplication */
    const Mat4 mult(const float o) const;
    /** External scalar division */
    const Mat4 div(const float o) const;
    /** Vector multiplication by vec4 */
    const Vec4 mult(const Vec4& o) const;
    /** Vector multiplication by vec3 */
    const Vec3 mult(const Vec3& o) const;

    /* ADDITIONAL METHODS */
    /** Set Vector to Zeros **/
    void zeros();

    /** GL methods */
    static const Mat4 Translate(const Vec3 &t);
    static const Mat4 Scale(const Vec3 &t);
    static const Mat4 Scale(float t);
    static const Mat4 RotationX(float angle);
    static const Mat4 RotationY(float angle);
    static const Mat4 RotationZ(float angle);
    static const Mat4 TRS(const Mat4& translation, const Mat4& rotation, const Mat4& scale);
    static const Mat4 Frustum(float left, float right, float bottom, float top, float near, float far);
    static const Mat4 Perspective(float fovy, float aspect, float znear, float zfar);
    static const Mat4 Ortho(float left, float right, float bottom, float top, float znear, float zfar);
    static const Mat4 LookAt(const Vec3 &eye, const Vec3 &center = Vec3(0, 0, 0), const Vec3 &up = Vec3(0, 1, 0));
  private:
#if ML_USE_SSE
    __m128 matrix_[4];
#else  
    alignas(alignof(float))float matrix_[16];
    static uint32_t mat_size_;
#endif    
  };
}
#endif