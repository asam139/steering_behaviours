//
// Created by Saul Moreno Abril on 21/07/2018.
//

#include "movementUtils.h"
#include <mathlib/vec2.h>

void MovementUtils::SeekCalculate(KinematicStatus *state, const KinematicStatus *targetState, KinematicSteering* steering, const float maxSpeed) {
    state->acceleration = {0.0f, 0.0f};
    state->velocity = (targetState->position - state->position).normalized() * maxSpeed;

    steering->acceleration = {0.0f, 0.0f};
    steering->angularAcceleration = 0.0f;
}