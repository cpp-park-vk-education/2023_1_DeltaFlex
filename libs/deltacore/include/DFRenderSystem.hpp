#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <DFvec2.hpp>
#include <iostream>

#include "DFTexture.hpp"

class DFRenderSystem
{
public:
    DFRenderSystem() : m_renderer(NULL) {}
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

    int RenderThickLine(const Vector2<int> &begin, const Vector2<int> &end, int width = 1)
    {
        SDL_Color color;
        SDL_GetRenderDrawColor(m_renderer, &color.r, &color.g, &color.b, &color.a);
        auto fixed_beg = begin + m_bcs;
        auto fixed_end = end + m_bcs;
        return thickLineRGBA(m_renderer,
                             fixed_beg.x, fixed_beg.y, fixed_end.x, fixed_end.y,
                             width,
                             color.r, color.g, color.b, color.a);
    }

    int RenderRectFilledUI(const SDL_Rect &rect)
    {
        return SDL_RenderFillRect(m_renderer, &rect);
    }

    int RenderRectHollowUI(const SDL_Rect &rect, uint32_t thickness = 1)
    {
        if (thickness == 1)
        {
            return SDL_RenderDrawRect(m_renderer, &rect);
        }
        else
        {
            SDL_Color color;
            SDL_GetRenderDrawColor(m_renderer, &color.r, &color.g, &color.b, &color.a);

            int rc = thickLineRGBA(
                m_renderer,
                rect.x - thickness / 2, rect.y, rect.x + rect.w + thickness / 2, rect.y,
                thickness,
                color.r, color.g, color.b, color.a);

            rc |= thickLineRGBA(
                m_renderer,
                rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h,
                thickness,
                color.r, color.g, color.b, color.a);

            rc |= thickLineRGBA(
                m_renderer,
                rect.x + rect.w + thickness / 2, rect.y + rect.h, rect.x - thickness / 2, rect.y + rect.h,
                thickness,
                color.r, color.g, color.b, color.a);

            rc |= thickLineRGBA(
                m_renderer,
                rect.x, rect.y + rect.h, rect.x, rect.y,
                thickness,
                color.r, color.g, color.b, color.a);
            return rc;
        }
    }

    void RenderFilledCircle(const Vector2<float> &center, const int radius)
    {
        SDL_Color color;
        SDL_GetRenderDrawColor(m_renderer, &color.r, &color.g, &color.b, &color.a);
        auto fixed_center = center + m_bcs;
        filledCircleRGBA(m_renderer,
                         fixed_center.x, fixed_center.y, radius,
                         color.r, color.g, color.b, color.a);
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

    int RenderTexture(const DFTexture &texture, SDL_Rect *srcrect, SDL_Rect *dstrect)
    {
        return RenderTexture(texture.m_texture, srcrect, dstrect);
    }

    int RenderTexture(const DFTexture &texture, const Vector2<float> &position, const SDL_Rect *srcrect = NULL)
    {
        SDL_Rect fixed_dstrect = {(int)position.x, (int)position.y, texture.width, texture.height};
        fixed_dstrect.x += m_bcs.x;
        fixed_dstrect.y += m_bcs.y;
        return SDL_RenderCopy(m_renderer, texture.m_texture, srcrect, &fixed_dstrect);
    }

    int RenderTextureUI(const DFTexture &texture, const Vector2<float> &position, const SDL_Rect *srcrect = NULL)
    {
        SDL_Rect fixed_dstrect = {(int)position.x, (int)position.y, texture.width, texture.height};
        return SDL_RenderCopy(m_renderer, texture.m_texture, srcrect, &fixed_dstrect);
    }

    int RenderTexture(SDL_Texture *texture, SDL_Rect *srcrect, SDL_Rect *dstrect)
    {
        SDL_Rect fixed_dstrect = {0};
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

    DFTexture CreateHollowCircleTex(unsigned radius, unsigned thickness)
    {
        SDL_Color color;
        SDL_GetRenderDrawColor(m_renderer, &color.r, &color.g, &color.b, &color.a);

        unsigned colorkey = 0xffff00ff;

        SDL_Surface *surf = SDL_CreateRGBSurface(0, (radius + thickness) * 2, (radius + thickness) * 2, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
        SDL_Renderer *software_renderer = SDL_CreateSoftwareRenderer(surf);

        SDL_SetRenderDrawColor(software_renderer, (colorkey >> 24) & 0xff, (colorkey >> 16) & 0xff, (colorkey >> 8) & 0xff, colorkey & 0xff);
        SDL_SetRenderDrawBlendMode(software_renderer, SDL_BLENDMODE_NONE);

        SDL_RenderClear(software_renderer);

        filledCircleRGBA(software_renderer, radius, radius, radius, color.r, color.g, color.b, color.a);
        filledCircleRGBA(software_renderer, radius, radius, radius - thickness, (colorkey >> 24) & 0xff, (colorkey >> 16) & 0xff, (colorkey >> 8) & 0xff, colorkey & 0xff);

        SDL_SetColorKey(surf, SDL_TRUE, colorkey);

        DFTexture circ(m_renderer, surf);
        
        SDL_DestroyRenderer(software_renderer);
        SDL_FreeSurface(surf);

        return std::move(circ);
    }

    DFTexture CreateTextureFromSurface(SDL_Surface *surface)
    {
        return {m_renderer, surface};
    }

    DFTexture CreateTextureFromFile(const std::string &f)
    {
        SDL_Surface *surf = IMG_Load(f.c_str());
        if (!surf)
        {
            throw std::runtime_error("Unable to load surface");
        }
        DFTexture tex(m_renderer, surf);
        SDL_FreeSurface(surf);
        return std::move(tex);
    }

    DFTexture CreateTextureText(const std::string &text, const std::string &font_path, const int font_size, const SDL_Color &text_color)
    {
        TTF_Font *fnt = TTF_OpenFont(font_path.c_str(), font_size);
        if (!fnt)
        {
            throw std::runtime_error(TTF_GetError());
        }
        SDL_Surface *surf = TTF_RenderText_Solid(fnt, text.c_str(), text_color);
        if (!surf)
        {
            throw std::runtime_error("Error occured while creating texture");
        }
        DFTexture tex(m_renderer, surf);
        TTF_CloseFont(fnt);
        SDL_FreeSurface(surf);
        return std::move(tex);
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

    static Vector2<int> const &GetOrigin()
    {
        return m_bcs;
    }

    ~DFRenderSystem()
    {
        SDL_DestroyRenderer(m_renderer);
    }

private:
    static Vector2<int> m_bcs;
    SDL_Renderer *m_renderer;
};
