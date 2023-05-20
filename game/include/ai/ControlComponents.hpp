#pragma once

#include "Model.hpp"
#include "Evolution.hpp"
#include "PhysicsComponent.hpp"

class Model;
class StickmanPhysicsComponent;

class StickmanRestarter: public DFComponent
{
private:
    StickmanPhysicsComponent *my_stickman;

public:
    void onInit(DFEntity &gameObject);
    void RestartStickman();
};

class EraComponent: public DFComponent
{

private:
    std::vector<DFEntity*> stickmans;
    int era;
    int time;
    int best;
    int multi;

public:
    EraComponent(std::vector<DFEntity*> stickmans): stickmans(stickmans){}
    void onInit(DFEntity &gameObject);
    void Restart();
    std::vector<Model*> GetModels();
    void Update();
};

class StickmanAI: public DFComponent
{

friend EraComponent;

private:
    StickmanPhysicsComponent *my_stickman;
    Model *model;

public:
    void onInit(DFEntity &gameObject);
    void Update();
    bool getActive();
};
