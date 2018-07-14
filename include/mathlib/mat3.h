//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#ifndef __ML_MAT3_H__
#define __ML_MAT3_H__ 1

#include "defines.h"
#include "vec3.h"

#include <iostream>

#if ML_USE_SSE
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>      //TODO Untested SSE outside MSCV
#endif  
#endif

namespace MathLib {

  class Mat3 {
  public:
    /** Default constructor. Sets to zeros */
    Mat3();

    /** Copy constructor
    @param o Matrix to copy from */
    Mat3(const Mat3& o);

    /** Constructor from three vec3 columns*/
    Mat3(const Vec3& c0, const Vec3& c1, const Vec3& c2);

    /** Constructor from a 9-position float array */
    Mat3(const float o[9]);

    /** Destructor */
    ~Mat3();

    /** Assignment operator
    @param o Matrix to copy from */
    Mat3& operator=(const Mat3& o);

    /** Returns a column, the same as getColumn(idx) */
    const Vec3 operator[](unsigned short index) const;

    /** Returns a column */
    const Vec3 getColumn(unsigned short index) const;

    /** Returns a row */
    const Vec3 getRow(unsigned short index) const;

    /** Returns a row SSE */
#if ML_USE_SSE
    const __m128 getRow_sse(unsigned short index) const;
#endif

    /** Internal addition operator */
    Mat3& operator+=(const Mat3& o);
    /* Internal substraction operator */
    Mat3& operator-=(const Mat3& o);
    /** Internal multiplication operator */
    Mat3& operator*=(const Mat3& o);
    /** Internal scalar multiplication */
    Mat3& operator*=(float o);
    /** Internal scalar division */
    Mat3& operator/=(float o);

    /** External addition */
    const Mat3 operator+(const Mat3& o) const;
    /** External substraction */
    const Mat3 operator-(const Mat3& o) const;
    /** External multiplication */
    const Mat3 operator*(const Mat3& o) const;
    /** External scalar multiplication */
    const Mat3 operator*(float o) const;
    /** External scalar division */
    const Mat3 operator/(float o) const;

    /** Vector multiplication */
    const Vec3 operator*(const Vec3& o) const;

    /** Transpose Matrix */
    const Mat3 transpose() const;

    /** Load identity Matrix */
    static const Mat3 identity();

    /* Named methods */
    /** Internal addition */
    Mat3& addEq(const Mat3& o);
    /** Internal substraction */
    Mat3& subEq(const Mat3& o);
    /** Internal mutiplication */
    Mat3& multEq(const Mat3& o);
    /** Internal scalar mutiplication */
    Mat3& multEq(const float o);
    /** Internal scalar division */
    Mat3& divEq(const float o);
    /** External addition */
    const Mat3 add(const Mat3& o) const;
    /** External substraction */
    const Mat3 sub(const Mat3& o) const;
    /** External multiplication */
    const Mat3 mult(const Mat3& o) const;
    /** External scalar multiplication */
    const Mat3 mult(const float o) const;
    /** External scalar division */
    const Mat3 div(const float o) const;
    /** Vector multiplication */
    const Vec3 mult(const Vec3& o) const;

    /* ADDITIONAL METHODS */
    /** Set Vector to Zeros **/
    void zeros();
  private:
#if ML_USE_SSE
    __m128 matrix_[3];
#else  
      alignas(alignof(float))float matrix_[9];
      static uint32_t mat_size_;
#endif

  };
}
#endif