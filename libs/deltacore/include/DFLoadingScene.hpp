#pragma once

#include <SDL2/SDL_image.h>

#include <DFScene.hpp>
#include <DFScUpdParams.hpp>

class DFLoadingScene: public DFScene
{
private:
    SDL_Surface *surf;
    SDL_Texture *texture;

    SDL_Rect src;
    SDL_Rect dst;
public:
    DFLoadingScene();
    void onRenderTextures(DFScUpdParams_t &render_data);
    void onSceneStart(DFScUpdParams_t &render_data);
    void onHandleFrame(DFScUpdParams_t &render_data);
};