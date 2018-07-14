//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#ifndef __ML_VEC2_H__
#define __ML_VEC2_H__ 1

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

  class Vec2 {
    public:
      enum Comp {
        /** Position */
        X = 0,
        Y = 1,
        /** Color */
        R = 0,
        G = 1,
        /** Texture coords */
        U = 0,
        V = 1
      };

      /** Default constructor. Sets to zeros */
      Vec2();

      /** Copy constructor
      @param o Vector to copy from */
      Vec2(const Vec2&o);

      /** Constructor using a pair of float values
      @param u1 The first vector component
      @param u2 The second vector component*/
      Vec2(const float u1, const float u2);

      /** Constructor using a __m128
      @param o __128 to create */
#if ML_USE_SSE    
      Vec2(const __m128 o);
#endif

      /** Destructor */
      ~Vec2();

      /** Returns the first component */
      const float x() const;
      float& x();
      /** Returns the second component */
      const float y() const;
      float& y();      

      /** Returns the __m128 */
#if ML_USE_SSE   
      const __m128 sse_val() const;
      __m128& sse_val();
#endif


      /** Subscript operators */
      /** @param index You can use one of the enums defined for vec2
      * X,Y,R,G,U,V*/
      const float operator[](uint16_t index) const;  // subscript without modifying
      float& operator[](uint16_t index);  // Subscript modifying

      /** Assignment operator
      @param o Vector to copy from */
      Vec2& operator=(const Vec2& o);

      /** Unary minus (-x,-y) */
      const Vec2 operator-() const;

      /** Internal addition operator */
      Vec2& operator+=(const Vec2& o);
      /** Internal substraction operator */
      Vec2& operator-=(const Vec2& o);
      /** Internal scalar multiplication */
      Vec2& operator*=(const float o);
      /** Internal scalar division */
      Vec2& operator/=(const float o);

      /** External addition */
      const Vec2 operator+(const Vec2& o) const;
      /** External substraction */
      const Vec2 operator-(const Vec2& o) const;
      /** External scalar multiplication */
      const Vec2 operator*(const float o) const;
      /** External scalar division */
      const Vec2 operator/(const float o) const;

      /** Dot product */
      float operator*(const Vec2& o) const;

      /** Equal operator */
      inline const bool operator==(Vec2 &o);
      /** Non-Equal operator */
      inline const bool operator!=(Vec2 &o);

      /* Named methods */
      /** Internal addition */
      Vec2& addEq(const Vec2& o);
      /** Internal substraction */
      Vec2& subEq(const Vec2& o);
      /** Internal scalar mutiplication */
      Vec2& multEq(const float o);
      /** Internal scalar division */
      Vec2& divEq(const float o);
      /** External addition */
      const Vec2 add(const Vec2& o) const;
      /** External substraction */
      const Vec2 sub(const Vec2& o) const;
      /** External scalar multiplication */
      const Vec2 mult(const float o) const;
      /** External scalar division */
      const Vec2 div(const float o) const;

      /* Vector operations */
      /** Dot product */
      float dot(const Vec2& o) const;

      /** Returns length of the current vector */
      float length() const;
      /** Returns squared length of the current vector*/
      float length2() const;
      /** Returns the vector normalized */
      const Vec2 normalized() const;
      /** Returns a tangent vector (-y,x) */
      const Vec2 tangent() const;
      /** Truncate by a scalar */
      const Vec2 trunc(const float o) const;

      /* Additional */
      /** Set Vector to Zeros **/
      void zeros();

      /** Conversion to Polar (degrees) **/
      void toPolar(float &dist, float &ang, const bool use_rads = true) const;
      /** Conversion from Polar (degrees)**/
      void fromPolar(const float dist, const float ang, const bool use_rads = true);

    private:
#if ML_USE_SSE
      __m128 vec_;
#else
      alignas(alignof(float)) float vec_[2];
      static uint32_t vec_size_;
#endif
  };

  /** Output stream for vec2 */
  std::ostream& operator<<(std::ostream& left, const Vec2& v);
}
#endif