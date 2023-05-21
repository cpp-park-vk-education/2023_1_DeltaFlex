#include <PointMass.hpp>
#include <Link.hpp>
#include <iostream>
#include <utility>

PointMass::PointMass(Vector2<float> &pos, float mass, float damping)
    : m_pos(pos),
    m_oldPos(pos),
    m_acceleration(),
    m_mass(mass),
    m_damping(damping),
    m_pinned(false),
    m_pinPos{}
{
    links.reserve(INITIAL_LINKS);
}

void PointMass::applyForce(Vector2<float> &force)
{
    m_acceleration += force / m_mass;
}

void PointMass::applyForce(Vector2<float> &&force)
{
    applyForce(force);
}

void PointMass::updatePhysics()
{
    applyForce({ 0, m_mass * GRAVITY });

    Vector2<float> velocity = m_pos - m_oldPos;

    velocity *= 0.99f;

    float dtSquared = DFEngine::deltaTime;
    dtSquared *= dtSquared;

    Vector2<float> posNext = m_pos + velocity + (m_acceleration * dtSquared * 0.5f);

    m_oldPos = m_pos;
    m_pos = posNext;

    m_acceleration = { 0, 0 };
}

void PointMass::pinTo(Vector2<float> &&pinPoint)
{
    m_pinned = true;
    m_pinPos = std::exchange(pinPoint, nullptr);
}

void PointMass::pinTo(const Vector2<float> &pinPoint)
{
    m_pinned = true;
    m_pinPos = pinPoint;
}

void PointMass::solveConstraints(float width, float height)
{
    for (auto &link : links)
    {
        link->solve();
    }

    if (m_pos.y < 1)
    {
        m_pos.y = 2 - m_pos.y;
    }
    if (m_pos.y > height - 1)
    {
        m_pos.y = 2 * (height - 1) - m_pos.y;
    }

    if (m_pos.x < 1)
    {
        m_pos.x = 2 - m_pos.x;
    }
    if (m_pos.x > width - 1)
    {
        m_pos.x = 2 * (width - 1) - m_pos.x;
    }

    if (m_pinned)
    {
        m_pos = m_pinPos;
    }
}

void PointMass::attachTo(PointMass &p, float restingDist, float stiffness, bool draw)
{
    links.emplace_back(std::make_shared<Link>(*this, p, restingDist, stiffness, draw)); // TODO
}

PointMass &PointMass::getLinkPoint()
{
    return links[0]->m_p2;
}

void PointMass::draw(const SDL_Color &color, DFRenderSystem &render_system)
{
    if (!links.empty())
    {
        // std::cout << "minigyg)\n";
        for (auto &link : links)
        {
            link->draw(color, render_system);
        }
    }
    else
    {
        render_system.SetColor(color);
        render_system.RenderPoint(m_pos);
        render_system.SetColor(0, 0, 0);
    }
}
