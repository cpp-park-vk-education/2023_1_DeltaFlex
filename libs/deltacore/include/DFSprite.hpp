#pragma once

#include <SDL2/SDL_image.h>

#include <DFComponent.hpp>
#include <DFPosition.hpp>
#include <DFScUpdParams.hpp>

class DFSprite:public DFComponent
{
private:
    SDL_Rect sprite_rect;
    DFPosition &target_position;

    int x_offset, y_offset;
    int baseWidth, baseHeight;

    SDL_Surface *surface;
    SDL_Texture *texture;
public:
    DFSprite(const char *resoursePath, DFPosition &tp, int _x_offset, int _y_offset);
    DFSprite(const char *resoursePath, DFPosition &tp);
    ~DFSprite();

    int getHeight() { return sprite_rect.h; }
    int getWidth() { return sprite_rect.w; }
    void onRenderTextures(DFScUpdParams_t &render_data);
    void Draw(DFScUpdParams_t &render_data);
};