#pragma once
#include "MainMenuButton.hpp"

class MainMenuPlay : public MainMenuButton
{
public:
    void onClick()
    {
        DFEngine::Instance->SwitchScene("game");
    }
};

class MainMenuOptions : public MainMenuButton
{
public:
    void onClick()
    {

    }
};

class MainMenuExit : public MainMenuButton
{
public:
    void onClick()
    {
        DFEngine::exitGame();
    }
};