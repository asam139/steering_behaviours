//
// Created by Saul Moreno Abril on 21/07/2018.
//

#include "movementUtils.h"
#import <debug_draw.h>
#include <agent.h>
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
                                       const float maxRotation, const float slowAngle, const float fixedTime) {
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

void MovementUtils::WanderCalculate(KinematicStatus *state, KinematicSteering *steering,
                                    const float wanderOffset, const float wanderRadius,
                                    const float wanderRate, const float maxAcceleration,
                                    const float maxRotation, const float slowAngle, float fixedTime) {
    //update wander orientation, rate * binomial distribution
    float wanderOrientation = state->orientation;
    wanderOrientation += wanderRate * randomFloat(-1.0f, 1.0f);

    KinematicStatus new_target;
    //orientation of new target facing combinated orientation
    new_target.orientation = wanderOrientation + state->orientation;

    MathLib::Vec2 charOrient; //orientation of character as vector
    charOrient.fromPolar(1.0f, state->orientation);
    MathLib::Vec2 targetOrient; //orientation of new target as vector
    targetOrient.fromPolar(1.0f, new_target.orientation);

    //the center of the circle
    new_target.position = state->position + (charOrient * wanderOffset);

    //position of the target in the circle
    new_target.position += targetOrient * wanderRadius;

    DebugDraw::drawCross(new_target.position, 0x00, 0x00, 0xFF, 0xFF);

    //delegate to face behavior
    FaceCalculate(state, &new_target, steering, maxRotation, slowAngle, fixedTime);

    //linear to full acceleration in direction of orientation
    steering->acceleration = charOrient * maxAcceleration;
}

// Flocking

MathLib::Vec2 MovementUtils::FlockingAlignment(Agent& agent, const float maxRadius) {
    MathLib::Vec2 v = {0.0f, 0.0f};
    int neighborCount = 0;

    std::vector< std::shared_ptr<Agent>>* agentGroup = agent.getAgentGroup();
    for (auto a : *agentGroup) {
        if (a.get() != &agent) {
            const float distance = (a->getKinematic()->position - agent.getKinematic()->position).length();
            if (distance < maxRadius) {
                v = v + a->getKinematic()->velocity;
                neighborCount++;
            }
        }
    }

    if (neighborCount == 0) {
        return v;
    }

    v = v / neighborCount;

    if (v.length() > 0) {
        v = v.normalized();
    }

    return v;
}

MathLib::Vec2 MovementUtils::FlockingCohesion(Agent &agent, const float maxRadius) {
    MathLib::Vec2 v = {0.0f, 0.0f};
    int neighborCount = 0;

    std::vector< std::shared_ptr<Agent>>* agentGroup = agent.getAgentGroup();
    for (auto &a : *agentGroup) {
        if (a.get() != &agent) {
            const float distance = (a->getKinematic()->position - agent.getKinematic()->position).length();
            if (distance < maxRadius) {
                v = v + a->getKinematic()->position;
                neighborCount++;
            }
        }
    }

    if (neighborCount == 0) {
        return v;
    }

    v = v / neighborCount;

    v = v - agent.getKinematic()->position;

    if (v.length() > 0) {
        v = v.normalized();
    }

    return v;
}

MathLib::Vec2 MovementUtils::FlockingSeparation(Agent& agent, const float maxRadius) {
    MathLib::Vec2 v = {0.0f, 0.0f};
    int neighborCount = 0;

    std::vector< std::shared_ptr<Agent>>* agentGroup = agent.getAgentGroup();
    for (auto a : *agentGroup) {
        if (a.get() != &agent) {
            const MathLib::Vec2 direction = a->getKinematic()->position - agent.getKinematic()->position;
            const float distance = direction.length();
            if (distance < maxRadius) {
                v = v + direction;
                neighborCount++;
            }
        }
    }

    if (neighborCount == 0) {
        return v;
    }

    v = v / neighborCount;
    v = v * -1;

    if (v.length() > 0) {
        v = v.normalized();
    }

    return v;
}