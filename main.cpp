#include <iostream>

#include "SteeringBehavioursConfig.h"

int main (int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stdout,"Version %d.%d\n",
                steering_behaviours_VERSION_MAJOR,
                steering_behaviours_VERSION_MINOR);
        return 1;
    }
    return 0;
}