#pragma once

#include "DFComponent.hpp"
#include "PointMass.hpp"
#include "StickmanCircle.hpp"
#include <vector>

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

constexpr float BODY_HEIGHT = 50;

constexpr std::size_t INITIAL_POINTMASSES = 10;

class StickmanPhysicsComponent : public DFComponent
{
private:
    std::vector<PointMass *> m_pointMasses;
    std::vector<StickmanCircle *> m_stickmanCircles;

public:
    SDL_Color m_color;

public:
    void onInit(DFEntity &gameObject) override
    {
        Vector2<float> &pos = gameObject.transform.position;

        m_pointMasses.reserve(INITIAL_POINTMASSES);

        float bodyHeight = 50;

        float headLength = bodyHeight / 7.5f;
        float headWidth = headLength * .75f;

        auto head = PointMass(pos);
        head.m_mass = 4;

        auto shoulder = PointMass(pos);
        shoulder.m_mass = 26;

        head.attachTo(shoulder, 5/4*headLength, 1);

        auto elbowL = PointMass(pos);
        auto elbowR = PointMass(pos);
        elbowL.m_mass = 2;
        elbowR.m_mass = 2;
        elbowL.attachTo(shoulder, headLength*3/2, 1);
        elbowR.attachTo(shoulder, headLength*3/2, 1);

        auto handL = PointMass(pos);
        auto handR = PointMass(pos);
        handL.m_mass = 2;
        handR.m_mass = 2;
        handL.attachTo(elbowL, headLength*2, 1);
        handR.attachTo(elbowR, headLength*2, 1);

        auto pelvis = PointMass(pos);
        pelvis.m_mass = 15;
        pelvis.attachTo(shoulder, headLength*3.5, 0.8);
        pelvis.attachTo(head, headLength*4.75, 0.02, false);

        auto kneeL = PointMass(pos);
        auto kneeR = PointMass(pos);
        kneeL.m_mass = 10;
        kneeR.m_mass = 10;
        kneeL.attachTo(pelvis, headLength*2, 1);
        kneeR.attachTo(pelvis, headLength*2, 1);

        auto footL = PointMass(pos);
        auto footR = PointMass(pos);
        footL.m_mass = 5;
        footR.m_mass = 5;
        footL.attachTo(kneeL, headLength*2, 1);
        footR.attachTo(kneeR, headLength*2, 1);

        footL.attachTo(shoulder, headLength*7.5, 1e-3, false);
        footR.attachTo(shoulder, headLength*7.5, 1e-3, false);

        StickmanCircle headCircle = StickmanCircle(headLength * .75, {40, 40});
        headCircle.attachToPointMass(head);

        // physics.addPoint(headCircle);
    
        m_pointMasses.push_back(head);
        m_pointMasses.push_back(shoulder);
        m_pointMasses.push_back(pelvis);
        m_pointMasses.push_back(elbowL);
        m_pointMasses.push_back(elbowR);
        m_pointMasses.push_back(handL);
        m_pointMasses.push_back(handR);
        m_pointMasses.push_back(kneeL);
        m_pointMasses.push_back(kneeR);
        m_pointMasses.push_back(footL);
        m_pointMasses.push_back(footR);
    }

    ~StickmanPhysicsComponent()
    {
        for (auto &p : m_pointMasses)
        {
            delete p;
        }

        for (auto &p : m_stickmanCircles)
        {
            delete p;
        }
    }

    void Update() override
    {
        for (auto &p : m_pointMasses)
        {
            p->solveConstraints(WIDTH, HEIGHT);
        }

        for (auto &p : m_stickmanCircles)
        {
            p->solveConstraints(WIDTH, HEIGHT);
        }

        for (auto &p : m_pointMasses)
        {
            p->updatePhysics();
        }
    }

    void Draw(DFScUpdParams_t &render_data)
    {
        for (auto &pm : m_pointMasses)
        {
            pm->draw(m_color, render_data);
        }

        for (auto &c : m_stickmanCircles)
        {
            c->draw(m_color, render_data);
        }
    }

    void addStickmanCircle(StickmanCircle &c)
    {
        m_stickmanCircles.emplace_back(c);
    }

    // void removeStickmanCircle(StickmanCircle &c)
    // {

    // }
};
