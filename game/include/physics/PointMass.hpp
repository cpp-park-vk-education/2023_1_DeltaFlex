#pragma once

#include "DFvec2.hpp"
#include "DFEngine.hpp"
#include "DFScUpdParams.hpp"

#include <vector>

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
    PointMass(Vector2<float> &pos, float mass = 1, float damping = 20);
    PointMass(Vector2<float> &&pos, float mass = 1, float damping = 20): PointMass(pos, mass, damping) {}

    void applyForce(Vector2<float> &force);

    void applyForce(Vector2<float> &&force);

    void updatePhysics();

    void pinTo(Vector2<float> &&pinPoint);
    void pinTo(const Vector2<float> &pinPoint);
    
    void solveConstraints(float width, float height);
    void attachTo(PointMass &p, float restingDist, float stiffness, bool draw = true);

    void draw(const SDL_Color &color, DFRenderSystem &render_system);
    PointMass &getLinkPoint();

};
