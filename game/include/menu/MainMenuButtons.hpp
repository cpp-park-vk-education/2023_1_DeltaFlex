#pragma once
#include "../UiButton.hpp"

class MainMenuPlay : public UiButton
{
public:
    void onClick()
    {
        DFEngine::Instance->SwitchScene("game");
    }
};

class MainMenuOptions : public UiButton
{
public:
    void onClick()
    {
        DFEngine::Instance->SwitchScene("options-volume");
    }
};

class MainMenuExit : public UiButton
{
public:
    void onClick()
    {
        DFEngine::exitGame();
    }
};
