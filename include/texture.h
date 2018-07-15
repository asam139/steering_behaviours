//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __TEXTURE_H__
#define __TEXTURE_H__ 1

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(const char* path);
    bool loadFromRenderedText(const char* textureText, const SDL_Color& textColor, TTF_Font* font, const bool shadow = false, const bool wrapped = false);
    void free();
    void setColor(const uint8_t red, const uint8_t green, const uint8_t blue) const;
    void setBlendMode(const SDL_BlendMode blending) const;
    void setAlpha(const uint8_t alpha) const;
    int getWidth() const { return width_; };
    int getHeight() const { return height_; };
protected:
    void renderText(const uint32_t x, const uint32_t y, const SDL_Rect* clip = nullptr, const float angle = 0.0, const SDL_Point* center = nullptr, const SDL_RendererFlip flip = SDL_FLIP_NONE) const;
private:
    SDL_Texture * texture_ = nullptr;
    int width_ = 0;
    int height_ = 0;
    uint32_t r_mask_, g_mask_, b_mask_, a_mask_;
};

#endif