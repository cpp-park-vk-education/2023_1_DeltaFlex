#pragma once

#include "DFComponent.hpp"
#include "DFEntity.hpp"
#include "ControlComponents.hpp"
#include "DFInputSystem.hpp"

class StickmanAI;

class StickmanPlayer: public DFComponent
{

private:
    StickmanAI *my_stickman;
    bool moveFlag;

public:
    void onInit(DFEntity &gameObject);
    void Update();
};
