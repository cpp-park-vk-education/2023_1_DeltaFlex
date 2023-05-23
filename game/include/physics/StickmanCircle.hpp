#pragma once

#include "PointMass.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>
void DrawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius);

class StickmanCircle
{
public:
    // friend PointMass;
    float m_radius;
    std::shared_ptr<PointMass> m_attachedPointMass;

public:
    StickmanCircle(float radius, Vector2<float> pmLocation)
        : m_radius(radius),
        m_attachedPointMass(new PointMass(pmLocation))
    {
    }

    void solveConstraints(float width, float height)
    {
        if (!m_attachedPointMass)
            throw std::runtime_error("Attached mass not specified");

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

        m_attachedPointMass->m_pos = { x, y };
    }

    void attachToPointMass(std::shared_ptr<PointMass> &p)
    {
        m_attachedPointMass = p;
    }

    void draw(const SDL_Color &color, DFRenderSystem &render_system)
    {
        // SDL_Renderer *renderer = render_system.getRenderer();
        // SDL_SetRenderDrawColor(
        //     renderer,
        //     color.r,
        //     color.g,
        //     color.b,
        //     color.a
        // );
#ifndef DEVELOPMENT
        filledCircleRGBA(render_system.getRenderer(),
            m_attachedPointMass->m_pos.x, m_attachedPointMass->m_pos.y, m_radius,
            color.r, color.g, color.b, color.a);
#else
        render_system.SetColor(color);
        render_system.RenderCircle(
            m_attachedPointMass->m_pos.x,
            m_attachedPointMass->m_pos.y,
            m_radius
        );
#endif
        // render_system.SetColor(0, 0, 0);
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
};
