//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2017                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ / 
//                                                       |___/___/\____/  
//----------------------------------------------------------------------------

#ifndef __ML_VEC4_H__
#define __ML_VEC4_H__ 1

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

  class Vec4 {
    public:
      enum Comp {
        /** Position */
        X = 0,
        Y = 1,
        Z = 2,
        W = 3,
        /** Color */
        R = 0,
        G = 1,
        B = 2,
        A = 3,
        /** Texture coords */
        U = 0,
        V = 1,
        S = 2,
        TT = 3
      };

      /** Default constructor. Sets to zeros */
      Vec4();

      /** Copy constructor
      @param o Vector to copy from */
      Vec4(const Vec4& o);

      /** Constructor from a vec3 and a float
      @param o A vec3
      @param u4 The fourth vector component
      */
      Vec4(const Vec3& o, const float u4);

      /** Constructor using three float values
      @param u1 The first vector component
      @param u2 The second vector component
      @param u3 The third vector component
      @param u4 The fourth vector component
      */
      Vec4(const float u1, const float u2, const float u3, const float u4);

      /** Constructor using a __m128
      @param o __128 to create */
  #if ML_USE_SSE
      Vec4(const __m128 o);
  #endif
      
      /** Destructor */
      ~Vec4();

      /** Assignment operator
      @param o Vector to copy from */
      Vec4& operator=(const Vec4& o);

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
      /** Returns the fourth component */
      const float w() const;
      float& w();

      /** Returns the __m128 */
  #if ML_USE_SSE    //SSE enabled
      const __m128 sse_val() const;
      __m128& sse_val();
  #endif

      /** Unary minus (-x,-y, -z) */
      const Vec4 operator-() const;

      /** Internal addition operator */
      Vec4& operator+=(const Vec4& o);
      /** Internal substraction operator */
      Vec4& operator-=(const Vec4& o);
      /** Internal scalar multiplication */
      Vec4& operator*=(float o);
      /** Internal scalar division */
      Vec4& operator/=(float o);

      /** External addition */
      const Vec4 operator+(const Vec4& o) const;
      /** External substraction */
      const Vec4 operator-(const Vec4& o) const;
      /** External scalar multiplication */
      const Vec4 operator*(float o) const;
      /** External scalar division */
      const Vec4 operator/(float o) const;

      /** Dot product */
      float operator*(const Vec4& o) const;

      /** Equal operator */
      inline const bool operator==(Vec4 &o);
      /** Non-Equal operator */
      inline const bool operator!=(Vec4 &o);

      /** Returns length of the current vector */
      float length() const;
      /** Returns squared length of the current vector*/
      float length2() const;
      /** Returns the vector normalized */
      const Vec4 normalized() const;

      /* Named methods */
      /** Internal addition */
      Vec4& addEq(const Vec4& o);
      /** Internal substraction */
      Vec4& subEq(const Vec4& o);
      /** Internal scalar mutiplication */
      Vec4& multEq(const float o);
      /** Internal scalar division */
      Vec4& divEq(const float o);
      /** External addition */
      const Vec4 add(const Vec4& o) const;
      /** External substraction */
      const Vec4 sub(const Vec4& o) const;
      /** External scalar multiplication */
      const Vec4 mult(const float o) const;
      /** External scalar division */
      const Vec4 div(const float o) const;
      /** Dot product */
      float dot(const Vec4& o) const;

      /* ADDITIONAL METHODS */
      /** Set Vector to Zeros **/
      void zeros();
    private:
#if ML_USE_SSE
      __m128 vec_;
#else  
      alignas(alignof(float)) float vec_[4];
      static uint32_t vec_size_;
#endif
  };

  /** Output stream for vec3 */
  std::ostream& operator<<(std::ostream& left, const Vec4& v);

}
#endif