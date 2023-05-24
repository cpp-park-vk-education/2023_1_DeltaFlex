#include "PhysicsComponent.hpp"

#include <array>
#include "DFEntity.hpp"
#include <cmath>

#include <DFWorldScene.hpp>

void StickmanPhysicsComponent::onInit(DFEntity &gameObject)
{
    ai = gameObject.getComponent<StickmanAI>();

    Vector2<float> &pos = gameObject.transform.position;

    m_pointMasses.reserve(INITIAL_POINTMASSES);

    float bodyHeight = 300;

    float headLength = bodyHeight / 7.5f;
    float headWidth = headLength * .75f;

    m_pointMasses.emplace_back(pos + Vector2<float>(0, 20));
    PointMass &head = m_pointMasses.back();
    head.m_mass = 0.5;

    m_pointMasses.emplace_back(pos + Vector2<float>(0, 0));
    PointMass &shoulder = m_pointMasses.back();
    shoulder.m_mass = 1;

     m_pointMasses.emplace_back(pos + Vector2<float>(0, -40));
    PointMass &pelvis = m_pointMasses.back();
    pelvis.m_mass = 1;

    m_pointMasses.emplace_back(pos + Vector2<float>(-10, 0));
    PointMass &elbowL = m_pointMasses.back();
    m_pointMasses.emplace_back(pos + Vector2<float>(+10, 0));
    PointMass &elbowR = m_pointMasses.back();
    elbowL.m_mass = 1;
    elbowR.m_mass = 1;

    m_pointMasses.emplace_back(pos + Vector2<float>(-10, -20));
    PointMass &handL = m_pointMasses.back();
    m_pointMasses.emplace_back(pos + Vector2<float>(+10, +20));
    PointMass &handR = m_pointMasses.back();
    handL.m_mass = 0.5;
    handR.m_mass = 0.5;

    m_pointMasses.emplace_back(pos + Vector2<float>(-10, -40));
    PointMass &kneeL = m_pointMasses.back();
    m_pointMasses.emplace_back(pos + Vector2<float>(+10, -40));
    PointMass &kneeR = m_pointMasses.back();
    kneeL.m_mass = 3;
    kneeR.m_mass = 3;

    m_pointMasses.emplace_back(pos + Vector2<float>(10, 20));
    PointMass &footL = m_pointMasses.back();
    m_pointMasses.emplace_back(pos + Vector2<float>(10, 20));
    PointMass &footR = m_pointMasses.back();
    footL.m_mass = 3;
    footR.m_mass = 3;

    m_stickmanCircles.emplace_back(headLength * .75f, Vector2<float>(40.f, 40.f));
    StickmanCircle &headCircle = m_stickmanCircles.back();

    head.attachTo(shoulder, 5 / 4 * headLength, 1);
    elbowL.attachTo(shoulder, headLength * 3 / 2, 1);
    elbowR.attachTo(shoulder, headLength * 3 / 2, 1);
    handL.attachTo(elbowL, headLength * 2, 1);
    handR.attachTo(elbowR, headLength * 2, 1);
    pelvis.attachTo(shoulder, headLength * 3.5, 0.8);
    pelvis.attachTo(head, headLength * 4.f, 0.02, false);
    kneeL.attachTo(pelvis, headLength * 2, 1);
    kneeR.attachTo(pelvis, headLength * 2, 1);
    footL.attachTo(kneeL, headLength * 2, 1);
    footR.attachTo(kneeR, headLength * 2, 1);
    footL.attachTo(shoulder, headLength * 7.5, 1e-3, false);
    footR.attachTo(shoulder, headLength * 7.5, 1e-3, false);
    headCircle.attachToPointMass(&head);

    // physics.addPoint(headCircle);
    // addStickmanCircle(headCircle);

    // m_pointMasses.emplace_back(std::move(head));
    // m_pointMasses.emplace_back(std::move(shoulder));
    // m_pointMasses.emplace_back(std::move(pelvis));
    // m_pointMasses.emplace_back(std::move(elbowL));
    // m_pointMasses.emplace_back(std::move(elbowR));
    // m_pointMasses.emplace_back(std::move(handL));
    // m_pointMasses.emplace_back(std::move(handR));
    // m_pointMasses.emplace_back(std::move(kneeL));
    // m_pointMasses.emplace_back(std::move(kneeR));
    // m_pointMasses.emplace_back(std::move(footL));
    // m_pointMasses.emplace_back(std::move(footR));
}

void StickmanPhysicsComponent::Start()
{
    DFEntity::Find("Camera")->getComponent<DFCameraComponent>()->SetTarget(
        m_pointMasses[2].m_pos);
}

// ~StickmanPhysicsComponent()
// {
//     // for (auto &p : m_pointMasses)
//     // {
//     //     delete p;
//     // }

//     // for (auto &p : m_stickmanCircles)
//     // {
//     //     delete p;
//     // }
// }

void StickmanPhysicsComponent::Update()
{
    for (auto &p : m_pointMasses)
    {
        p.solveConstraints(WIDTH, HEIGHT);
    }

    for (auto &p : m_stickmanCircles)
    {
        p.solveConstraints(WIDTH, HEIGHT);
    }

    for (auto &p : m_pointMasses)
    {
        p.updatePhysics();
    }
}

void StickmanPhysicsComponent::Draw(DFRenderSystem &render_system)
{
    // auto *r = render_data.renderer.get();
    // SDL_RenderDrawLine(r, 0, 0, 100, 100);
    // std::cout << "MINI RYR PISHE)\n";
    // if (!ai->getActive())
    //     return;

    for (auto &pm : m_pointMasses)
    {
        pm.draw(m_color, render_system);
    }

    for (auto &c : m_stickmanCircles)
    {
        c.draw(m_color, render_system);
    }
    // SDL_SetRenderDrawColor(render_data.renderer.get(), 0, 0, 0, 255);
    render_system.SetColor(0, 0, 0);
}

void StickmanPhysicsComponent::addStickmanCircle(StickmanCircle &c)
{
    m_stickmanCircles.emplace_back(c);
}

// void removeStickmanCircle(StickmanCircle &c)
// {

// }

void StickmanPhysicsComponent::Move(int limb, double angle)
{
    if (limb == 1)
        return;

    angle = angle * (M_PI / 180);

    float x = m_pointMasses[limb].m_pos.x;
    float y = m_pointMasses[limb].m_pos.y;

    PointMass &point_c = m_pointMasses[limb].getLinkPoint();

    float x_c = point_c.m_pos.x;
    float y_c = point_c.m_pos.y;

    if (limb == 2)
    {
        limb = 1;
        int tmp = x;
        x = x_c;
        x_c = tmp;
        tmp = y;
        y = y_c;
        y_c = tmp;
    }

    m_pointMasses[limb].m_pos.x = cos(angle) * (x - x_c) - sin(angle) * (y - y_c) + x_c;
    m_pointMasses[limb].m_pos.y = sin(angle) * (x - x_c) + cos(angle) * (y - y_c) + y_c;
}

void StickmanPhysicsComponent::MoveAll(std::array<float, 6> angles)
{
    int i = 0;
    for (float angle : angles)
    {
        if (i != 2)
            angle /= 3;
        else
            angle /= 2;
        m_pointMasses[0].m_pos.y -= 1.4;
        Move(i, angle);
        i++;
    }

    Move(7, angles[2] / 4);
    Move(8, angles[2] / 4);

}

std::array<float, 12> StickmanPhysicsComponent::GetCoords()
{
    std::array<float, 12> coords;
    for (size_t i = 0; i < 6; i++)
    {
        coords[i * 2] = (m_pointMasses[i].m_pos.x - m_pointMasses[2].m_pos.x);
        coords[i * 2 + 1] = m_pointMasses[i].m_pos.y - m_pointMasses[2].m_pos.y;
    }

    float min = *std::min(coords.begin(), coords.end());
    float max = *std::max(coords.begin(), coords.end());

    for (size_t i = 0; i < 12; i++)
        coords[i] = (coords[i] - min) / (max - min);

    return coords;
}
