#include "ControlComponents.hpp"
#include <DFInputSystem.hpp>
#include <DFWorldScene.hpp>

void StickmanRestarter::onInit(DFEntity &gameObject)
{
    my_stickman = gameObject.getComponent<StickmanPhysicsComponent>();
    RestartStickman();
}

void StickmanRestarter::RestartStickman()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-400, 400);

    Vector2<float> align(dist(gen), 475.873 - 70);
    my_stickman->m_pointMasses[0].m_pos = align + Vector2<float>(619.665, 23.703);
    my_stickman->m_pointMasses[1].m_pos = align + Vector2<float>(619.665, 56.6235);
    my_stickman->m_pointMasses[2].m_pos = align + Vector2<float>(619.659, 137.391);
    my_stickman->m_pointMasses[3].m_pos = align + Vector2<float>(619.63, 83.7396);
    my_stickman->m_pointMasses[4].m_pos = align + Vector2<float>(619.669, 83.7609);
    my_stickman->m_pointMasses[5].m_pos = align + Vector2<float>(619.554, 137.073);
    my_stickman->m_pointMasses[6].m_pos = align + Vector2<float>(619.664, 137.094);
    my_stickman->m_pointMasses[7].m_pos = align + Vector2<float>(634.704, 190.655);
    my_stickman->m_pointMasses[8].m_pos = align + Vector2<float>(604.614, 190.794);
    my_stickman->m_pointMasses[9].m_pos = align + Vector2<float>(638.774, 313.988);
    my_stickman->m_pointMasses[10].m_pos = align + Vector2<float>(600.544, 314.127);
    for (auto &x : my_stickman->m_pointMasses)
    {
        x.m_acceleration = { 0, 0 };
        x.m_oldPos = x.m_pos;
    }
    my_stickman->m_pointMasses[2].pinTo({my_stickman->m_pointMasses[2].m_pos.x, my_stickman->m_pointMasses[2].m_pos.y});
    my_stickman->m_pointMasses[9].pinTo({my_stickman->m_pointMasses[9].m_pos.x, my_stickman->m_pointMasses[9].m_pos.y});
    my_stickman->m_pointMasses[10].pinTo({my_stickman->m_pointMasses[10].m_pos.x, my_stickman->m_pointMasses[10].m_pos.y});
}

void StickmanAI::onInit(DFEntity &gameObject)
{
    my_stickman = gameObject.getComponent<StickmanPhysicsComponent>();
    
    attack_model = new Model(my_stickman, "../game_base_models/attack.txt");
    protect_model = new Model(my_stickman, "../game_base_models/protect.txt");
    idle_model = new Model(my_stickman);
    model = idle_model;

    walk_model = new WalkModel(my_stickman);
    battle_model = new BattleModel(my_stickman);
    
    battle_action = 0;
    walk_action = 0;
    walk_flag = false;

    battle_delay = 60;
    walk_delay = 60;
}

void StickmanAI::Update()
{
    if (walk_delay > 0)
    {
        walk_delay--;
    }
    else
    {
        walk_action = walk_model->predict();
        walk_delay = 15;
    }

    if (battle_delay > 0)
    {
        battle_delay--;
    }
    else
    {
        battle_action = battle_model->predict();

        if (battle_action == 0)
            model = idle_model;
        else if (battle_action == 1)
            model = attack_model;
        else if (battle_action == 2)
            model = protect_model;
        battle_delay = 15;
    }

    doWalk();
    doBattle();
}

bool StickmanAI::getActive()
{
    return model->getActive();
}

void StickmanAI::doBattle()
{
    auto result = model->predict();
    my_stickman->MoveAll(result);
}

void StickmanAI::doWalk()
{   
    if (my_stickman->m_pointMasses[2].m_pinPos.x < 30)
        walk_action = 2;

    if (walk_action == 1)
    {
        my_stickman->m_pointMasses[2].pinTo({my_stickman->m_pointMasses[2].m_pinPos.x - 2, my_stickman->m_pointMasses[2].m_pinPos.y});
        if (walk_flag)
            my_stickman->m_pointMasses[9].pinTo({my_stickman->m_pointMasses[9].m_pinPos.x - 4, my_stickman->m_pointMasses[9].m_pinPos.y});
        else
            my_stickman->m_pointMasses[10].pinTo({my_stickman->m_pointMasses[10].m_pinPos.x - 4, my_stickman->m_pointMasses[10].m_pinPos.y});
        if (my_stickman->m_pointMasses[9].m_pinPos.x - my_stickman->m_pointMasses[10].m_pinPos.x > 50)
            walk_flag = true;
        if (my_stickman->m_pointMasses[10].m_pinPos.x - my_stickman->m_pointMasses[9].m_pinPos.x > 50)
            walk_flag = false;
    }
    else if (walk_action == 2)
    {
        my_stickman->m_pointMasses[2].pinTo({my_stickman->m_pointMasses[2].m_pinPos.x + 2, my_stickman->m_pointMasses[2].m_pinPos.y});
        if (walk_flag)
            my_stickman->m_pointMasses[9].pinTo({my_stickman->m_pointMasses[9].m_pinPos.x + 4, my_stickman->m_pointMasses[9].m_pinPos.y});
        else
            my_stickman->m_pointMasses[10].pinTo({my_stickman->m_pointMasses[10].m_pinPos.x + 4, my_stickman->m_pointMasses[10].m_pinPos.y});
        if (my_stickman->m_pointMasses[9].m_pinPos.x - my_stickman->m_pointMasses[10].m_pinPos.x > 50)
            walk_flag = false;
        if (my_stickman->m_pointMasses[10].m_pinPos.x - my_stickman->m_pointMasses[9].m_pinPos.x > 50)
            walk_flag = true;
    }
}
