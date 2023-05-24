#pragma once

#include "DFvec2.hpp"
#include "DFEngine.hpp"
#include "DFScUpdParams.hpp"

#include <vector>
#include <utility>

constexpr float GRAVITY = 980.0f;

constexpr std::size_t INITIAL_LINKS = 10;
class Link;
class PointMass
{
public:
    Vector2<float> m_pos;
    Vector2<float> m_oldPos;
    Vector2<float> m_acceleration;

    float m_mass;
    float m_damping;

    bool m_pinned;
    Vector2<float> m_pinPos;

    std::vector<std::shared_ptr<Link>> links;

public:
    // PointMass(PointMass &&other)
    // {
    //     m_pos = std::exchange(other.m_pos, { 0, 0 });
    //     m_oldPos = std::exchange(other.m_oldPos, { 0, 0 });
    //     m_acceleration = std::exchange(other.m_acceleration, { 0, 0 });

    //     m_mass = other.m_mass;
    //     m_damping = other.m_damping;
    //     m_pinned = other.m_pinned;

    //     links = std::exchange(other.links, { 0 });
    // }
    PointMass(Vector2<float> &pos, float mass = 1, float damping = 20);
    PointMass(Vector2<float> &&pos, float mass = 1, float damping = 20) : PointMass(pos, mass, damping) {}

    void applyForce(Vector2<float> &force);

    void applyForce(Vector2<float> &&force);

    void updatePhysics();

    void pinTo(Vector2<float> &&pinPoint);
    void pinTo(const Vector2<float> &pinPoint);

    void solveConstraints(float width, float height);
    std::shared_ptr<Link> attachTo(PointMass &p, float restingDist, float stiffness, bool draw = true);

    void draw(const SDL_Color &color, DFRenderSystem &render_system);
    PointMass &getLinkPoint();

};
