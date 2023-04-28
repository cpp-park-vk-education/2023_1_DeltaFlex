#pragma once

#include "Link.hpp"

#include "DFvec2.hpp"
#include "DFEngine.hpp"
#include "DFScUpdParams.hpp"

#include <vector>

constexpr float GRAVITY = 980.0f;

constexpr std::size_t INITIAL_LINKS = 10;

class PointMass
{
public:
    Vector2<float> m_pos;
    Vector2<float> m_oldPos;
    Vector2<float> m_acceleration;

    float m_mass;
    float m_damping;

    std::vector<Link *> links;

public:
    PointMass(Vector2<float> &pos, float mass = 1, float damping = 20)
        : m_pos(pos),
          m_oldPos(pos),
          m_acceleration(),
          m_mass(mass),
          m_damping(damping)
    {
        links.reserve(INITIAL_LINKS);
    }

    ~PointMass()
    {
        for (auto &link : links)
        {
            delete link;
        }
    }

    void applyForce(Vector2<float> &force)
    {
        m_acceleration += force / m_mass;
    }

    void applyForce(Vector2<float> &&force)
    {
        applyForce(force);
    }

    void updatePhysics()
    {
        applyForce({0, m_mass * GRAVITY});

        Vector2<float> velocity = m_pos - m_oldPos;

        velocity *= 0.99f;

        float dtSquared = DFEngine::deltaTime;
        dtSquared *= dtSquared;

        Vector2<float> posNext = m_pos + velocity + (m_acceleration * dtSquared * 0.5f);

        m_oldPos = m_pos;
        m_pos = posNext;

        m_acceleration = {0, 0};
    }

    void solveConstraints(float width, float height)
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
    }

    void attachTo(PointMass &p, float restingDist, float stiffness, bool draw = true)
    {
        links.push_back(new Link(*this, p, restingDist, stiffness, draw)); // TODO
    }

    void draw(const SDL_Color &color, DFScUpdParams_t &render_data)
    {
        if (!links.empty())
        {
            for (auto &link : links)
            {
                link->draw(color, render_data);
            }
        }
        else
        {
            SDL_Renderer *renderer = render_data.renderer.get();
            SDL_SetRenderDrawColor(
                renderer,
                color.r,
                color.g,
                color.b,
                color.a
            );

            SDL_RenderDrawPointF(renderer, m_pos.x, m_pos.y);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        }
    }
};
