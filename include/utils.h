//
// Created by Saul Moreno Abril on 15/07/2018.
//

#ifndef STEERING_BEHAVIOURS_UTILS_H
#define STEERING_BEHAVIOURS_UTILS_H

#include <cstdlib>
#include <assert.h>

float RandomFloat(float min, float max)
{
    // this  function assumes max > min, you may want
    // more robust error checking for a non-debug build
    assert(max > min);
    float random = ((float) rand()) / (float) RAND_MAX;

    // generate (in your case) a float between 0 and (4.5-.78)
    // then add .78, giving you a float between .78 and 4.5
    float range = max - min;
    return (random*range) + min;
}

// Floating-point modulo
// The result (the remainder) has same sign as the divisor.
// Similar to matlab's mod(); Not similar to fmod() -   Mod(-3,4)= 1   fmod(-3,4)= -3
template<typename T>
T Mod(T x, T y)
{
    static_assert(!std::numeric_limits<T>::is_exact , "Mod: floating-point type expected");

    if (0. == y)
        return x;

    double m= x - y * floor(x/y);

    // handle boundary cases resulted from floating-point cut off:

    if (y > 0)              // modulo range: [0..y)
    {
        if (m>=y)           // Mod(-1e-16             , 360.    ): m= 360.
            return 0;

        if (m<0 )
        {
            if (y+m == y)
                return 0  ; // just in case...
            else
                return y+m; // Mod(106.81415022205296 , _TWO_PI ): m= -1.421e-14
        }
    }
    else                    // modulo range: (y..0]
    {
        if (m<=y)           // Mod(1e-16              , -360.   ): m= -360.
            return 0;

        if (m>0 )
        {
            if (y+m == y)
                return 0  ; // just in case...
            else
                return y+m; // Mod(-106.81415022205296, -_TWO_PI): m= 1.421e-14
        }
    }

    return m;
}

// wrap [rad] angle to [-PI..PI)
inline double WrapPosNegPI(double fAng)
{
    return Mod(fAng + M_PI, 2 * M_PI) - M_PI;
}

// wrap [rad] angle to [0..TWO_PI)
inline double WrapTwoPI(double fAng)
{
    return Mod(fAng, 2 * M_PI);
}

// wrap [deg] angle to [-180..180)
inline double WrapPosNeg180(double fAng)
{
    return Mod(fAng + 180., 360.) - 180.;
}

// wrap [deg] angle to [0..360)
inline double Wrap360(double fAng)
{
    return Mod(fAng ,360.);
}

inline float sign(float value) {
    // Nonzero integral value if arg is negative, ​0​ otherwise.
    if (value == -0.0f){
        return -0.0f;
    } else if (value == +0.0f){
        return +0.0f;
    } else if (value < 0.0f) {
        return -1.0f;
    } else if (value > 0.f){
        return 1.0f;
    } else  {
        return 0.0f;
    }
}

#endif //STEERING_BEHAVIOURS_UTILS_H
