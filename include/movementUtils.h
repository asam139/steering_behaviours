//
// Created by Saul Moreno Abril on 21/07/2018.
//

#ifndef STEERING_BEHAVIOURS_MOVEMENTUTILS_H
#define STEERING_BEHAVIOURS_MOVEMENTUTILS_H


#include "defines.h"

class Agent;

class MovementUtils {
public:
    static void SeekCalculate(KinematicStatus *state, const KinematicStatus *targetState, KinematicSteering* steering,
                              const float maxSpeed);

    static void AlignCalculate(KinematicStatus *state, const KinematicStatus *targetState, KinematicSteering* steering,
                               const float maxRotation, const float slowAngle, const float fixedTime);
    static void PursueCalculate(KinematicStatus *state, const KinematicStatus *targetState, KinematicSteering* steering,
                                const float maxSpeed, const float maxPrediction);
    static void FaceCalculate(KinematicStatus *state, const KinematicStatus *targetState, KinematicSteering* steering,
                                      const float maxRotation, const float slowAngle, const float fixedTime);
    static void LookGoingCalculate(KinematicStatus *state, const KinematicStatus *targetState, KinematicSteering* steering,
                                   const float maxRotation, const float slowAngle, const float fixedTime);
    static void WanderCalculate(KinematicStatus *state, KinematicSteering* steering,
                                const float wanderOffset, const float wanderRadius,
                                const float wanderRate, const float maxAcceleration,
                                const float maxRotation, const float slowAngle, float fixedTime);

    // Flocking
    static MathLib::Vec2 FlockingAlignment(Agent& agent, const float maxRadius);
    static MathLib::Vec2 FlockingCohesion(Agent& agent, const float maxRadius);
    static MathLib::Vec2 FlockingSeparation(Agent& agent, const float maxRadius);
};


#endif //STEERING_BEHAVIOURS_MOVEMENTUTILS_H
