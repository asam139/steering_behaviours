//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <sprite.h>

void Sprite::render() const {
  if (visible_) renderText(position_.x, position_.y, nullptr, angle_);
}

void Sprite::setVisible(const bool visible) {
  visible_ = visible;
}

void Sprite::setPositionUpLeft(const uint32_t x, const uint32_t y) {
  position_.x = x;
  position_.y = y;
}

void Sprite::setPosition(const uint32_t x, const uint32_t y) {
  position_.x = x - (getWidth() / 2);
  position_.y = y - (getHeight() / 2);
}

void Sprite::setRotation(const float angle) {
  angle_ = angle;
}