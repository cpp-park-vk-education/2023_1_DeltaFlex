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

    int RenderPoint(const Vector2<int> &point)
    {
        return SDL_RenderDrawPoint(m_renderer, point.x + m_bcs.x, point.y + m_bcs.y);
    }

    int RenderPoint(const Vector2<float> &point)
    {
        return SDL_RenderDrawPointF(m_renderer, point.x + m_bcs.x, point.y + m_bcs.y);
    }

    int RenderLine(const Vector2<int> &begin, const Vector2<int> &end)
    {
        auto fixed_beg = begin + m_bcs;
        auto fixed_end = end + m_bcs;
        return SDL_RenderDrawLine(m_renderer, fixed_beg.x, fixed_beg.y, fixed_end.x, fixed_end.y);
    }

    void RenderCircle(int32_t centreX, int32_t centreY, int32_t radius)
    {
        const int32_t diameter = (radius * 2);

        int32_t x = (radius - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        while (x >= y)
        {
            SDL_RenderDrawPoint(m_renderer, centreX + x + m_bcs.x, centreY - y + m_bcs.y);
            SDL_RenderDrawPoint(m_renderer, centreX + x + m_bcs.x, centreY + y + m_bcs.y);
            SDL_RenderDrawPoint(m_renderer, centreX - x + m_bcs.x, centreY - y + m_bcs.y);
            SDL_RenderDrawPoint(m_renderer, centreX - x + m_bcs.x, centreY + y + m_bcs.y);
            SDL_RenderDrawPoint(m_renderer, centreX + y + m_bcs.x, centreY - x + m_bcs.y);
            SDL_RenderDrawPoint(m_renderer, centreX + y + m_bcs.x, centreY + x + m_bcs.y);
            SDL_RenderDrawPoint(m_renderer, centreX - y + m_bcs.x, centreY - x + m_bcs.y);
            SDL_RenderDrawPoint(m_renderer, centreX - y + m_bcs.x, centreY + x + m_bcs.y);

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
    }

    int RenderTexture(SDL_Texture *texture, SDL_Rect *srcrect, SDL_Rect *dstrect)
    {
        SDL_Rect fixed_dstrect = { 0 };
        if (dstrect)
        {
            fixed_dstrect = *dstrect;
        }
        else
        {
            fixed_dstrect.w = 1280;
            fixed_dstrect.h = 720;
        }
        fixed_dstrect.x += m_bcs.x;
        fixed_dstrect.y += m_bcs.y;
        return SDL_RenderCopy(m_renderer, texture, srcrect, &fixed_dstrect);
    }

    SDL_Texture *CreateTextureFromSurface(SDL_Surface *surface)
    {
        return SDL_CreateTextureFromSurface(m_renderer, surface);
    }

    SDL_Texture *CreateTextureFromFile(const std::string &f)
    {
        return IMG_LoadTexture(m_renderer, f.c_str());
    }

    Vector2<float> WorldToScreen(const Vector2<float> &point)
    {
        return point + m_bcs;
    }

    Vector2<float> ScreenToWorld(const Vector2<float> &point)
    {
        return point - m_bcs;
    }

    int SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
    {
        return SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    }

    int SetColor(const SDL_Color &clr)
    {
        return SDL_SetRenderDrawColor(m_renderer, clr.r, clr.g, clr.b, clr.a);
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