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
    Link(PointMass &pm1, PointMass &pm2, float restingDist, float stiffness, bool draw = true);
    void solve();
    void draw(const SDL_Color &color, DFScUpdParams_t &render_data);
};
