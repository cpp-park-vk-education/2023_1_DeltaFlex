#pragma once

#include <SDL2/SDL.h>

#include <utility>
class DFTexture
{
    friend class DFRenderSystem;
public:
    DFTexture() : width(0), height(0), m_texture(nullptr) {}
    ~DFTexture()
    {
        SDL_DestroyTexture(m_texture);
    }

    DFTexture(const DFTexture &other) = delete;

    DFTexture &operator=(DFTexture &&other)
    {
        m_texture = std::exchange(other.m_texture, nullptr);
        width = other.width;
        height = other.height;
        return *this;
    }

    DFTexture(DFTexture &&other):
        width(other.width), height(other.height)
    {
        m_texture = std::exchange(other.m_texture, nullptr);
    }

    int width, height;
protected:
    DFTexture(SDL_Renderer *renderer, SDL_Surface *surface) : width(surface->w), height(surface->h)
    {
        m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    }

    DFTexture(SDL_Texture *texture, int width, int height) : width(width), height(height), m_texture(texture)
    {}

private:
    SDL_Texture *m_texture;
};