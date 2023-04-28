#pragma once

#include "PointMass.hpp"
#include "DFScUpdParams.hpp"

class Link
{
private:
    friend PointMass;

    float m_restingDist;
    float m_stiffness;
    bool m_draw;

    PointMass &m_p1;
    PointMass &m_p2;

public:
    Link(PointMass &pm1, PointMass &pm2, float restingDist, float stiffness, bool draw = true)
        : m_p1(pm1),
          m_p2(pm2),
          m_restingDist(restingDist),
          m_stiffness(stiffness),
          m_draw(draw)
    {
    }

    void solve()
    {
        Vector2<float> delta = m_p1.m_pos - m_p2.m_pos;

        float dist = delta.length();

        float difference = (m_restingDist - dist) / dist;

        float im1 = 1.0f / m_p1.m_mass;
        float im2 = 1.0f / m_p2.m_mass;

        float p1Scalar = (im1 / (im1 + im2)) * m_stiffness;
        float p2Scalar = m_stiffness - p1Scalar;

        m_p1.m_pos += delta * p1Scalar * difference;
        m_p2.m_pos -= delta * p2Scalar * difference;
    }

    void draw(const SDL_Color &color, DFScUpdParams_t &render_data)
    {
        if (m_draw)
        {
            SDL_Renderer *renderer = render_data.renderer.get();
            SDL_SetRenderDrawColor(
                renderer,
                color.r,
                color.g,
                color.b,
                color.a
            );

            SDL_RenderDrawLineF(
                renderer,
                m_p1.m_pos.x,
                m_p1.m_pos.y,
                m_p2.m_pos.x,
                m_p2.m_pos.y
            );

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
    }
};
