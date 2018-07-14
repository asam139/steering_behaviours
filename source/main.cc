//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <game.h>
#include <defines.h>
#include <window.h>

int main(int,char*[]) {
  Window::instance().init(GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);

  {
    Game game;

    game.init();
    game.start();
    game.shutdown();
  }

  Window::instance().shutdown();

  return 0;
}