//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <debug_draw.h>
#include <window.h>
#include <defines.h>

float DebugDraw::delta_ = 0.01f;
bool DebugDraw::enabled_ = false;
uint16_t DebugDraw::hist_idx_ = 0;
Vec2 DebugDraw::hist_[MAX_HIST];

void DebugDraw::drawVector(const Vec2& pos, const Vec2& v,
  const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
  if (enabled_) {
    if (((v.x() > delta_) || (v.x() < -delta_)) && ((v.y() > delta_) || ((v.y() < -delta_)))) {
      SDL_Renderer* renderer = Window::instance().getRenderer();
      SDL_SetRenderDrawColor(renderer, r, g, b, a);
      SDL_RenderDrawLine(renderer, pos.x(), pos.y(), pos.x() + v.x(), pos.y() + v.y());

      const Vec2 p_vertex = pos + v;
      const Vec2 p_tmp = p_vertex - (v.normalized() * 5.0f);

      const float pi_q = M_PI / 4.0f;
      const Vec2 p_arrow1 = rotate2D(p_vertex, p_tmp, pi_q);
      const Vec2 p_arrow2 = rotate2D(p_vertex, p_tmp, -pi_q);

      SDL_RenderDrawLine(renderer, p_vertex.x(), p_vertex.y(), p_arrow1.x(), p_arrow1.y());
      SDL_RenderDrawLine(renderer, p_vertex.x(), p_vertex.y(), p_arrow2.x(), p_arrow2.y());
    }
  }
}

void DebugDraw::drawPositionHist(const Vec2& pos) {
  hist_[hist_idx_++ % MAX_HIST] = pos;

  if (enabled_) {
    for (uint16_t i = 0; i < MAX_HIST; ++i) {
      SDL_Renderer* renderer = Window::instance().getRenderer();
      SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderDrawPoint(renderer, (uint32_t)hist_[i].x(), (uint32_t)hist_[i].y());
    }
  }
}
