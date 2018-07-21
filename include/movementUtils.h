//
// Created by Saul Moreno Abril on 21/07/2018.
//

#ifndef STEERING_BEHAVIOURS_MOVEMENTUTILS_H
#define STEERING_BEHAVIOURS_MOVEMENTUTILS_H


#include "defines.h"

class MovementUtils {
public:
    static void SeekCalculate(KinematicStatus *state, const KinematicStatus *targetState, KinematicSteering* steering, const float maxSpeed);
};


#endif //STEERING_BEHAVIOURS_MOVEMENTUTILS_H
