#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <DFvec2.hpp>

class DFRenderSystem
{
public:
    DFRenderSystem() : m_bcs(0, 0), m_renderer(NULL) {}
    void setRenderer(SDL_Renderer *renderer)
    {
        m_renderer = renderer;
    }

    SDL_Renderer *getRenderer()
    {
        return m_renderer;
    }


    void Clear()
    {
        SDL_RenderClear(m_renderer);
    }

    void Present()
    {
        SDL_RenderPresent(m_renderer);
    }

    int RenderLine(const Vector2<int> &begin, const Vector2<int> &end)
    {
        auto fixed_beg = begin - m_bcs;
        auto fixed_end = end - m_bcs;
        return SDL_RenderDrawLine(m_renderer, fixed_beg.x, fixed_beg.y, fixed_end.x, fixed_end.y);
    }

    int RenderTexture(SDL_Texture *texture, SDL_Rect *srcrect, SDL_Rect *dstrect)
    {
        if (dstrect)
        {
            SDL_Rect fixed_dstrect = *dstrect;
            fixed_dstrect.x -= m_bcs.x;
            fixed_dstrect.y -= m_bcs.y;
            return SDL_RenderCopy(m_renderer, texture, srcrect, &fixed_dstrect);
        }
        return SDL_RenderCopy(m_renderer, texture, srcrect, dstrect);
    }

    SDL_Texture *CreateTextureFromSurface(SDL_Surface *surface)
    {
        return SDL_CreateTextureFromSurface(m_renderer, surface);
    }

    SDL_Texture *CreateTextureFromFile(const std::string &f)
    {
        return IMG_LoadTexture(m_renderer, f.c_str());
    }

    int SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
    {
        return SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    }

    void SetOrigin(const Vector2<int> &new_origin)
    {
        m_bcs = new_origin;
    }

    ~DFRenderSystem()
    {
        SDL_DestroyRenderer(m_renderer);
    }
private:
    Vector2<int> m_bcs;
    SDL_Renderer *m_renderer;
};