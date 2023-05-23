#include "PlayerControl.hpp"
#include "DFInputSystem.hpp"

void StickmanPlayer::onInit(DFEntity &gameObject)
{
    my_stickman = gameObject.getComponent<StickmanAI>();
    moveFlag = false;
}

void StickmanPlayer::Update()
{
    if (Input::GetKeyDown(KEYCODE_1))
    {
        my_stickman->model->load("../game_base_models/stay.txt");
    }
    else if (Input::GetKey(KEYCODE_A))
    {
        my_stickman->my_stickman->m_pointMasses[2]->pinTo({my_stickman->my_stickman->m_pointMasses[2]->m_pinPos.x - 2, my_stickman->my_stickman->m_pointMasses[2]->m_pinPos.y});
        if (moveFlag)
            my_stickman->my_stickman->m_pointMasses[9]->pinTo({my_stickman->my_stickman->m_pointMasses[9]->m_pinPos.x - 4, my_stickman->my_stickman->m_pointMasses[9]->m_pinPos.y});
        else
            my_stickman->my_stickman->m_pointMasses[10]->pinTo({my_stickman->my_stickman->m_pointMasses[10]->m_pinPos.x - 4, my_stickman->my_stickman->m_pointMasses[10]->m_pinPos.y});
        if (my_stickman->my_stickman->m_pointMasses[9]->m_pinPos.x - my_stickman->my_stickman->m_pointMasses[10]->m_pinPos.x > 50)
            moveFlag = true;
        if (my_stickman->my_stickman->m_pointMasses[10]->m_pinPos.x - my_stickman->my_stickman->m_pointMasses[9]->m_pinPos.x > 50)
            moveFlag = false;
    }
    if (Input::GetKey(KEYCODE_D))
    {
        my_stickman->my_stickman->m_pointMasses[2]->pinTo({my_stickman->my_stickman->m_pointMasses[2]->m_pinPos.x + 2, my_stickman->my_stickman->m_pointMasses[2]->m_pinPos.y});
        if (moveFlag)
            my_stickman->my_stickman->m_pointMasses[9]->pinTo({my_stickman->my_stickman->m_pointMasses[9]->m_pinPos.x + 4, my_stickman->my_stickman->m_pointMasses[9]->m_pinPos.y});
        else
            my_stickman->my_stickman->m_pointMasses[10]->pinTo({my_stickman->my_stickman->m_pointMasses[10]->m_pinPos.x + 4, my_stickman->my_stickman->m_pointMasses[10]->m_pinPos.y});
        if (my_stickman->my_stickman->m_pointMasses[9]->m_pinPos.x - my_stickman->my_stickman->m_pointMasses[10]->m_pinPos.x > 50)
            moveFlag = false;
        if (my_stickman->my_stickman->m_pointMasses[10]->m_pinPos.x - my_stickman->my_stickman->m_pointMasses[9]->m_pinPos.x > 50)
            moveFlag = true;
    }
    if (Input::GetKeyDown(KEYCODE_S))
    {
        if (my_stickman->my_stickman->m_pointMasses[2]->m_pinPos.y < 600)
            my_stickman->my_stickman->m_pointMasses[2]->pinTo({my_stickman->my_stickman->m_pointMasses[2]->m_pinPos.x, my_stickman->my_stickman->m_pointMasses[2]->m_pinPos.y += 50});
    }
    if (Input::GetKeyDown(KEYCODE_W))
    {
        if (my_stickman->my_stickman->m_pointMasses[2]->m_pinPos.y > 550)
            my_stickman->my_stickman->m_pointMasses[2]->pinTo({my_stickman->my_stickman->m_pointMasses[2]->m_pinPos.x, my_stickman->my_stickman->m_pointMasses[2]->m_pinPos.y -= 50});
    }
}
