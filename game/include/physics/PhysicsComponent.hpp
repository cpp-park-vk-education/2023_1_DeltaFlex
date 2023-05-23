#pragma once

#include "DFComponent.hpp"
#include "PointMass.hpp"
#include "StickmanCircle.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <math.h>
#include "ControlComponents.hpp"

#include <SatCollider.hpp>
#include <Link.hpp>
constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

constexpr float BODY_HEIGHT = 50;

constexpr std::size_t INITIAL_POINTMASSES = 10;

class StickmanAI;

class StickmanPhysicsComponent : public DFComponent
{
public:
    StickmanAI *ai;
    std::vector<std::shared_ptr<PointMass>> m_pointMasses;
    std::vector<std::shared_ptr<StickmanCircle>> m_stickmanCircles;

public:
    // SDL_Color m_color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF};
    SDL_Color m_color{.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF};

public:
    void onInit(DFEntity &gameObject) override;

    void Update() override;

    void Draw(DFRenderSystem &render_system) override;

    void addStickmanCircle(std::shared_ptr<StickmanCircle> &c);

    void Move(int limb, double angle);

    void MoveAll(std::array<float, 11> angles);

    bool CheckCollision(const SATCollider &collider)
    {
        for(auto &p_mass: m_pointMasses)
        {
            for (auto &p_link: p_mass->links)
            {
                if (p_link->m_collider.isColliding(collider))
                {
                    return true;
                }
            }
        }
        return false;
    };

    std::array<float, 22> GetCoords();

};