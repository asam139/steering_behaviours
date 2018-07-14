#include "SteeringBehavioursConfig.h"
#include <window.h>
#include <sprite.h>
#include <game.h>

#include <iostream>
int main (int argc, char *argv[]) {
    fprintf(stdout,"Version %d.%d\n", STEERING_BEHAVIOURS_VERSION_MAJOR, STEERING_BEHAVIOURS_VERSION_MINOR);

    Window::instance().init(GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);

    Game game;
    game.init();
    game.start();
    game.shutdown();

    Window::instance().shutdown();

    return 0;
}