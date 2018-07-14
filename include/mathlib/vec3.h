//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#ifndef __ML_VEC3_H__
#define __ML_VEC3_H__ 1

#include "defines.h"

#include <iostream>

#if ML_USE_SSE
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>      //TODO Untested SSE outside MSCV
#endif  
#endif

namespace MathLib {

  class Vec3 {
    public:
      enum Comp {
        /** Position */
        X = 0,
        Y = 1,
        Z = 2,
        /** Color */
        R = 0,
        G = 1,
        B = 2,
        /** Texture coords */
        U = 0,
        V = 1,
        S = 2
      };

      /** Default constructor. Sets to zeros */
      Vec3();

      /** Copy constructor
      @param o Vector to copy from */
      Vec3(const Vec3& o);

      /** Constructor using three float values
      @param u1 The first vector component
      @param u2 The second vector component
      @param u3 The third vector component
      */
      Vec3(const float u1, const float u2, const float u3);

      /** Constructor using a __m128
      @param o __128 to create */
#if ML_USE_SSE
      Vec3(const __m128 o);
#endif

      /** Destructor */
      ~Vec3();

      /** Assignment operator
      @param o Vector to copy from */
      Vec3& operator=(const Vec3& o);

      /** Subscript operators */
      /** You can use one of the enums defined for vec3
      * X,Y,Z,R,G,B,U,V,S
      */
      const float operator[](unsigned short index) const;
      float& operator[](unsigned short index);

      /** Returns the first component */
      const float x() const;
      float& x();
      /** Returns the second component */
      const float y() const;
      float& y();
      /** Returns the third component */
      const float z() const;
      float& z();
      /** Returns the __m128 */
#if ML_USE_SSE    //SSE enabled
      const __m128 sse_val() const;
      __m128& sse_val();
#endif

      /** Unary minus (-x,-y, -z) */
      const Vec3 operator-() const;

      /** Internal addition operator */
      Vec3& operator+=(const Vec3& o);
      /** Internal substraction operator */
      Vec3& operator-=(const Vec3& o);
      /** Internal scalar multiplication */
      Vec3& operator*=(float o);
      /** Internal scalar division */
      Vec3& operator/=(float o);

      /** External addition */
      const Vec3 operator+(const Vec3& o) const;
      /** External substraction */
      const Vec3 operator-(const Vec3& o) const;
      /** Cross product (tangent) */
      const Vec3 operator^(const Vec3& o) const;
      /** External scalar multiplication */
      const Vec3 operator*(float o) const;
      /** External scalar division */
      const Vec3 operator/(float o) const;

      /** Dot product */
      float operator*(const Vec3& o) const;

      /** Equal operator */
      inline const bool operator==(Vec3 &o);
      /** Non-Equal operator */
      inline const bool operator!=(Vec3 &o);

      /** Returns length of the current vector */
      float length() const;
      /** Returns squared length of the current vector*/
      float length2() const;
      /** Returns the vector normalized */
      const Vec3 normalized() const;
      /** Returns a tangent vector (cross product) */
      const Vec3 cross(const Vec3& o) const;

      /* Named methods */
      /** Internal addition */
      Vec3& addEq(const Vec3& o);
      /** Internal substraction */
      Vec3& subEq(const Vec3& o);
      /** Internal scalar mutiplication */
      Vec3& multEq(const float o);
      /** Internal scalar division */
      Vec3& divEq(const float o);
      /** External addition */
      const Vec3 add(const Vec3& o) const;
      /** External substraction */
      const Vec3 sub(const Vec3& o) const;
      /** External scalar multiplication */
      const Vec3 mult(const float o) const;
      /** External scalar division */
      const Vec3 div(const float o) const;
      /** Dot product */
      float dot(const Vec3& o) const;

      /* ADDITIONAL METHODS */
      /** Set Vector to Zeros **/
      void zeros();
    private:
#if ML_USE_SSE
      __m128 vec_;
#else  
      alignas(alignof(float)) float vec_[3];
      static uint32_t vec_size_;
#endif
  };

  /** Output stream for vec3 */
  std::ostream& operator<<(std::ostream& left, const Vec3& v);

}
#endif