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
        my_stickman->model = my_stickman->idle_model;
    }
    else if (Input::GetKeyDown(KEYCODE_1))
    {
        my_stickman->model = my_stickman->attack_model;
    }
    else if (Input::GetKeyDown(KEYCODE_1))
    {
        my_stickman->model = my_stickman->protect_model;
    }
    else if (Input::GetKey(KEYCODE_A))
    {
        my_stickman->walk_action = 1;
    }
    if (Input::GetKey(KEYCODE_D))
    {
        my_stickman->walk_action = 2;
    }
}
