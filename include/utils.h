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

#endif //STEERING_BEHAVIOURS_UTILS_H
