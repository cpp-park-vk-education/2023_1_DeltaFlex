#pragma once

#include "Model.hpp"
#include "WalkModel.hpp"
#include "BattleModel.hpp"
#include "Evolution.hpp"
#include "PhysicsComponent.hpp"
#include "PlayerControl.hpp"

#include <DFInputSystem.hpp>

class Model;
class WalkModel;
class BattleModel;
class EraComponent;
class Evolution;

class StickmanPhysicsComponent;
class StickmanPlayer;

class StickmanRestarter: public DFComponent
{
private:
    StickmanPhysicsComponent *my_stickman;

public:
    void onInit(DFEntity &gameObject);
    void RestartStickman();

    void Update()
    {
        if (Input::GetKeyDown(KEYCODE_R))
        {
            RestartStickman();
        }
    }
};

class StickmanAI: public DFComponent
{

friend StickmanPlayer;
friend EraComponent;
friend Evolution;

private:
    Model *attack_model;
    Model *protect_model;
    Model *idle_model;
    Model *model;

    StickmanPhysicsComponent *my_stickman;
    StickmanPhysicsComponent *stickman_1;
    WalkModel *walk_model;
    BattleModel *battle_model;

    int battle_action;
    int walk_action;
    bool walk_flag;
    bool legup_flag;

    int battle_delay;
    int walk_delay;

    static bool m_is_active;
    friend class StickmanStats;

protected:
    void doWalk();
    void doBattle();
    void doTrain();

public:
    void onInit(DFEntity &gameObject);
    void Start();
    void Update();
    bool getActive();
    
    static void setActiveSim(bool state);

    int training_model = 0;
    int training_time = 0;
};
