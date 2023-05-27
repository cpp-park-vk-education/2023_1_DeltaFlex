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
#include <StickmanStatsComponent.hpp>
constexpr int WIDTH = 2280;
constexpr int HEIGHT = 720;

constexpr float BODY_HEIGHT = 50;
class StickmanStats;
constexpr std::size_t INITIAL_POINTMASSES = 11;

class StickmanAI;

class StickmanPhysicsComponent : public DFComponent
{
public:
    StickmanAI *ai;
    StickmanPhysicsComponent *enemy;
    StickmanStats *my_stats;
    std::vector<PointMass> m_pointMasses;
    std::vector<StickmanCircle> m_stickmanCircles;
    std::vector<SATCollider> m_colliders;

private:
    static bool m_is_active;

public:
    // SDL_Color m_color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF};
    SDL_Color m_color{.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF};

public:
    void onInit(DFEntity &gameObject) override;

    void Start() override;
    void Update() override;

    void Draw(DFRenderSystem &render_system) override;

    void addStickmanCircle(StickmanCircle &c);

    void Move(int limb, double angle);

    void MoveAll(std::array<float, 6> angles);

    static void SetActiveSim(bool state);
    // bool CheckCollision(const SATCollider &collider)
    // {
    //     for(auto &p_mass: m_pointMasses)
    //     {
    //         for (auto &p_link: p_mass.links)
    //         {
    //             if (p_link->m_collider.isColliding(collider))
    //             {
    //                 return true;
    //             }
    //         }
    //     }
    //     return false;
    // };

    std::array<float, 12> GetCoords();

};
#include <DFInputSystem.hpp>
#include <DFEntity.hpp>
class TestRect : public DFComponent
{
public:
    Vector2<float> p1, p2;

    SATCollider m_collider;
    TestRect() : m_collider(p1, p2) {}

    void Update()
    {
        Vector2<float> mpos(Input::GetMouseX(), Input::GetMouseY());
        p1 = mpos - Vector2<float>{100, 0};
        p2 = mpos + Vector2<float>{100, 0};
        p1 -= DFRenderSystem::GetOrigin();
        p2 -= DFRenderSystem::GetOrigin();
        m_collider.RecalcPoints(5);
    }
    void Draw(DFRenderSystem &render_system)
    {
        for (auto &collider : DFEntity::Find("stickman_0")->getComponent<StickmanPhysicsComponent>()->m_colliders)
        {
            if (collider.isColliding(m_collider))
            {
                render_system.SetColor(255, 0, 0);
                break;
            }
        }
        m_collider.Draw(render_system);
        render_system.SetColor(0, 0, 0);

    }
};
