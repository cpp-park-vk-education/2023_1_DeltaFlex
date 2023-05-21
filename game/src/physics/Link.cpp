#include "Link.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>
Link::Link(PointMass &pm1, PointMass &pm2, float restingDist, float stiffness, bool draw)
    : m_p1(pm1),
    m_p2(pm2),
    m_restingDist(restingDist),
    m_stiffness(stiffness),
    m_draw(draw)
{
}

float Link::length() const
{
    Vector2<float> delta = m_p1.m_pos - m_p2.m_pos;
    return delta.length();
}

void Link::solve()
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

void Link::draw(const SDL_Color &color, DFRenderSystem &render_system)
{
    if (m_draw)
    {
        // render_system.SetColor(color.r, color.g, color.b, color.a);
        render_system.SetColor(color);
        render_system.RenderLine(m_p1.m_pos, m_p2.m_pos);
        // thickLineRGBA(renderer,
        //     m_p1.m_pos.x, m_p1.m_pos.y,
        //     m_p2.m_pos.x, m_p2.m_pos.y,
        //     1, color.r, color.g, color.g, color.a);
    }
}
