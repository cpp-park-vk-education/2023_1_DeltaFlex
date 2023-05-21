#pragma once

#include <memory>

#include <SDL2/SDL_render.h>
#include <DFRenderSystem.hpp>

struct DFScUpdParams_t
{
    // std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer *)> renderer;
    DFRenderSystem render_system;
    std::unique_ptr<SDL_Window, void(*)(SDL_Window *)> window;

    DFScUpdParams_t():
        render_system(),
        window(nullptr, SDL_DestroyWindow)
        {}

    ~DFScUpdParams_t()
    {
        window.release();
    }
};
