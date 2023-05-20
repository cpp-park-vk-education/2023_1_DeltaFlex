#pragma once

#include <memory>

#include <SDL2/SDL_render.h>

struct DFScUpdParams_t
{
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer *)> renderer;
    std::unique_ptr<SDL_Window, void(*)(SDL_Window *)> window;

    DFScUpdParams_t():
        renderer(nullptr, SDL_DestroyRenderer),
        window(nullptr, SDL_DestroyWindow)
        {}

    ~DFScUpdParams_t()
    {
        window.release();
        renderer.release();
    }
};
