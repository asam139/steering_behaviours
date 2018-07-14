cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
project(steering_behaviours)

# The version number.
set (STEERING_BEHAVIOURS_VERSION_MAJOR 1)
set (STEERING_BEHAVIOURS_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
        "${PROJECT_SOURCE_DIR}/SteeringBehavioursConfig.h.in"
        "${PROJECT_BINARY_DIR}/SteeringBehavioursConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")


add_executable(steering_behaviours main.cpp SteeringBehavioursConfig.h.in)

