//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <texture.h>
#include <window.h>
#include <defines.h>

#include <SDL/SDL_image.h>
#include <cstdio>



Texture::Texture() {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  r_mask_ = 0xff000000;
  g_mask_ = 0x00ff0000;
  b_mask_ = 0x0000ff00;
  a_mask_ = 0x000000ff;
#else
  r_mask_ = 0x000000ff;
  g_mask_ = 0x0000ff00;
  b_mask_ = 0x00ff0000;
  a_mask_ = 0xff000000;
#endif
}

Texture::~Texture() {
  free();
}

bool Texture::loadFromFile(const char* path) {
  SDL_Renderer* renderer = Window::instance().getRenderer();
  free();

  SDL_Texture* newTexture = nullptr;

  SDL_Surface* loadedSurface = IMG_Load(path);
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
  }
  else {
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == NULL) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
    }
    else {
      width_ = loadedSurface->w;
      height_ = loadedSurface->h;
    }

    SDL_FreeSurface(loadedSurface);
  }

  texture_ = newTexture;
  return texture_ != nullptr;
}

bool Texture::loadFromRenderedText(const char* textureText, const SDL_Color& textColor, TTF_Font* font, const bool shadow, const bool wrapped) {
  SDL_Renderer* renderer = Window::instance().getRenderer();
  free();

  int shadowOffset = 1;
  if (TTF_FontHeight(font) > 40) {
    shadowOffset = 2;
  }

  SDL_Surface* textSurface = nullptr;
  if (shadow) {
    SDL_Surface* textS;
    SDL_Surface* shadowS;

    if (wrapped) {
      textS = TTF_RenderText_Blended_Wrapped(font, textureText, textColor, WINDOW_WIDTH);
      shadowS = TTF_RenderText_Blended_Wrapped(font, textureText, SHADOW_COLOR, WINDOW_HEIGHT);
    }
    else {
      textS = TTF_RenderText_Blended(font, textureText, textColor);
      shadowS = TTF_RenderText_Blended(font, textureText, SHADOW_COLOR);
    }

    textSurface = SDL_CreateRGBSurface(0, textS->w + shadowOffset, textS->h + shadowOffset, 32, r_mask_, g_mask_, b_mask_, a_mask_);

    SDL_Rect r_dst;
    r_dst.x = shadowOffset; r_dst.y = shadowOffset; r_dst.w = shadowS->w; r_dst.h = shadowS->h;
    SDL_BlitSurface(shadowS, &shadowS->clip_rect, textSurface, &r_dst);

    r_dst.x = 0; r_dst.y = 0; r_dst.w = textS->w; r_dst.h = textS->h;
    SDL_BlitSurface(textS, &textS->clip_rect, textSurface, &r_dst);

    SDL_FreeSurface(shadowS);
    SDL_FreeSurface(textS);
  }
  else {
    if (wrapped) {
      textSurface = TTF_RenderText_Blended_Wrapped(font, textureText, textColor, WINDOW_WIDTH);
    }
    else {
      textSurface = TTF_RenderText_Blended(font, textureText, textColor);
    }
  }

  if (textSurface != NULL) {
    texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!texture_) {
      printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    else {
      width_ = textSurface->w;
      height_ = textSurface->h;
    }
    SDL_FreeSurface(textSurface);
  }
  else {
    printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
  }

  return texture_ != nullptr;
}

void Texture::free() {
  if (texture_) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    width_ = 0;
    height_ = 0;
  }
}

void Texture::setColor(const uint8_t red, const uint8_t green, const uint8_t blue) const {
  SDL_SetTextureColorMod(texture_, red, green, blue);
}

void Texture::setBlendMode(const SDL_BlendMode blending) const {
  SDL_SetTextureBlendMode(texture_, blending);
}

void Texture::setAlpha(const uint8_t alpha) const {
  SDL_SetTextureAlphaMod(texture_, alpha);
}

void Texture::renderText(const uint32_t x, const uint32_t y, const SDL_Rect* clip, const float angle, const SDL_Point* center, const SDL_RendererFlip flip) const {
  const float angle_rad = (angle * 180) / M_PI;
  SDL_Renderer* renderer = Window::instance().getRenderer();
  SDL_Rect renderQuad = { (int)x, (int)y, width_, height_ };

  if (clip) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  SDL_RenderCopyEx(renderer, texture_, clip, &renderQuad, angle_rad, center, flip);
}