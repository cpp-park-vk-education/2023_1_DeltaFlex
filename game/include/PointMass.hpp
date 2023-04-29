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

    std::vector<Link *> links;

public:
    PointMass(Vector2<float> &pos, float mass = 1, float damping = 20);
    PointMass(Vector2<float> &&pos, float mass = 1, float damping = 20): PointMass(pos, mass, damping) {}

    ~PointMass();

    void applyForce(Vector2<float> &force);

    void applyForce(Vector2<float> &&force);

    void updatePhysics();

    void solveConstraints(float width, float height);
    void attachTo(PointMass &p, float restingDist, float stiffness, bool draw = true);

    void draw(const SDL_Color &color, DFScUpdParams_t &render_data);
};