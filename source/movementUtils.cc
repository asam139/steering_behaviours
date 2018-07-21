//
// Created by Saul Moreno Abril on 21/07/2018.
//

#include "movementUtils.h"
#include <mathlib/vec2.h>

void MovementUtils::SeekCalculate(KinematicStatus *state, const KinematicStatus *targetState, KinematicSteering* steering,
                                  const float maxSpeed) {
    state->acceleration = {0.0f, 0.0f};
    state->velocity = (targetState->position - state->position).normalized() * maxSpeed;

    steering->acceleration = {0.0f, 0.0f};
    steering->angularAcceleration = 0.0f;
}


void MovementUtils::AlignCalculate(KinematicStatus *state, const KinematicStatus *targetState, KinematicSteering* steering,
                                   const float maxRotation, const float slowAngle, float fixedTime) {
    //rotation between character and target wrapped to (-PI, PI)
    const float rotation = wrapAnglePI(targetState->orientation - state->orientation);
    const float rotation_size = abs(rotation); //absolute value of rotation
    float target_rotation = maxRotation; //max
    if (rotation_size < slowAngle) { //inside the slow zone
        //speed of rotation slowing down
        target_rotation = (maxRotation * rotation_size) / slowAngle;
    }
    target_rotation *= sign(rotation); //positive or negative
    //angular acceleration adjusted to time
    steering->angularAcceleration = (target_rotation) / fixedTime;
    steering->acceleration = {0.0f, 0.0f};
}

void MovementUtils::PursueCalculate(KinematicStatus *state, const KinematicStatus *targetState, KinematicSteering* steering,
                                    const float maxSpeed, const float maxPrediction) {
    //distance to the target
    const float distance = (targetState->position - state->position).length();
    float speed = state->velocity.length(); //speed of character
    float prediction = maxPrediction; //max prediction
    if (speed > (distance / maxPrediction)) { //reasonable predicion
        prediction = distance / speed; //calc predicion time
    }
    KinematicStatus new_target = *targetState; //new target
    //position of new target
    new_target.position += targetState->velocity * prediction;

    //delegate to seek behavior with new target
    MovementUtils::SeekCalculate(state, &new_target, steering, maxSpeed);
}

void MovementUtils::FaceCalculate(KinematicStatus *state, const KinematicStatus *targetState, KinematicSteering* steering,
                              const float maxRotation, const float slowAngle, float fixedTime) {
    //direction to target
    const MathLib::Vec2 direction = targetState->position - state->position;
    KinematicStatus new_target = *targetState; //new target
    //orientation of new target facing direction
    new_target.orientation = atan2(direction.y(), direction.x());

    //delegate to align behavior with new target
    MovementUtils::AlignCalculate(state, &new_target, steering, maxRotation, slowAngle, fixedTime);
}

void MovementUtils::LookGoingCalculate(KinematicStatus *state, const KinematicStatus *targetState, KinematicSteering* steering,
                                       const float maxRotation, const float slowAngle, float fixedTime) {
    if (state->velocity.length() == 0) { //no movement
        steering->angularAcceleration = 0.0f;
        return;
    }
    KinematicStatus new_target = *targetState;
    //orientation of new target facing velocity
    new_target.orientation = atan2(state->velocity.y(), state->velocity.x());

    //delegate to align behavior with new target
    MovementUtils::AlignCalculate(state, &new_target, steering, maxRotation, slowAngle, fixedTime);
}