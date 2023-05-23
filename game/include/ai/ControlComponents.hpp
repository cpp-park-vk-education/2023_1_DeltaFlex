#pragma once

#include "Model.hpp"
#include "Evolution.hpp"
#include "PhysicsComponent.hpp"
#include "PlayerControl.hpp"

class Model;
class EraComponent;

class StickmanPhysicsComponent;
class StickmanPlayer;

class StickmanRestarter: public DFComponent
{
private:
    StickmanPhysicsComponent *my_stickman;

public:
    void onInit(DFEntity &gameObject);
    void RestartStickman();
};

class StickmanAI: public DFComponent
{

friend StickmanPlayer;
friend EraComponent;

private:
    StickmanPhysicsComponent *my_stickman;
    Model *model;

public:
    void onInit(DFEntity &gameObject);
    void Update();
    bool getActive();
};
