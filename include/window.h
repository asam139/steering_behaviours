//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __WINDOW_H__
#define __WINDOW_H__ 1

#include <SDL/SDL.h>

class Window {
  public:
    ~Window() {}
    Window(Window const&) = delete;
    void operator=(Window const&) = delete;

    static Window& instance() {
      static Window instance;
      return  instance;
    }

    bool init(const char* name, const uint32_t width, const uint32_t height);
    void shutdown();

    SDL_Window* getWindow() const { return window_; }
    SDL_Renderer* getRenderer() const { return renderer_; }
  private:
    Window() {}

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
};
#endif