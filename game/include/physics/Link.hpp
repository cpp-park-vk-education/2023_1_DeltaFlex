#pragma once

#include "PointMass.hpp"
#include "DFScUpdParams.hpp"
#include "../SatCollider.hpp"

class Link
{
private:
    friend PointMass;

    float m_restingDist;
    float m_stiffness;
    bool m_draw;

public:
    PointMass &m_p1;
    PointMass &m_p2;
    Link(PointMass &pm1, PointMass &pm2, float restingDist, float stiffness, bool draw = true);
    float length() const;
    void solve();
    void draw(const SDL_Color &color, DFRenderSystem &render_system);
};
