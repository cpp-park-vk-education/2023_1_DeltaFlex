#pragma once

#include "PointMass.hpp"

void DrawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

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

class StickmanCircle
{
private:
    // friend PointMass;
    float m_radius;
    PointMass *m_attachedPointMass;

public:
    StickmanCircle(float radius, Vector2<float> pmLocation)
        : m_radius(radius),
          m_attachedPointMass(new PointMass(pmLocation))
    {
    }

    ~StickmanCircle()
    {
        delete m_attachedPointMass;
    }

    void solveConstraints(float width, float height)
    {
        float x = m_attachedPointMass->m_pos.x;
        float y = m_attachedPointMass->m_pos.y;

        if (y < m_radius)
        {
            y = 2 * m_radius - y;
        }
        if (y > height - m_radius)
        {
            y = 2 * (height - m_radius) - y;
        }

        if (x < m_radius)
        {
            x = 2 * m_radius - x;
        }
        if (x > width - m_radius)
        {
            x = 2 * (width - m_radius) - x;
        }

        m_attachedPointMass->m_pos = {x, y};
    }

    void attachToPointMass(PointMass *p)
    {
        delete m_attachedPointMass;
        m_attachedPointMass = p;
    }

    void draw(const SDL_Color &color, DFScUpdParams_t &render_data)
    {
        SDL_Renderer *renderer = render_data.renderer.get();
        SDL_SetRenderDrawColor(
            renderer,
            color.r,
            color.g,
            color.b,
            color.a
        );

        DrawCircle(
            renderer, 
            m_attachedPointMass->m_pos.x,
            m_attachedPointMass->m_pos.y,
            m_radius
        );

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
};
