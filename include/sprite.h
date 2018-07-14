//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __SPRITE_H__
#define __SPRITE_H__ 1

#include <texture.h>

class Sprite : public Texture {
public:
  Sprite() {};
  ~Sprite() {};

  void setPositionUpLeft(const uint32_t x, const uint32_t y);
  void setPosition(const uint32_t x, const uint32_t y);
  void setVisible(const bool visible = true);
  void render() const;
private:
  SDL_Point position_ { 0, 0 };
  bool visible_ { true };
protected:
};

#endif