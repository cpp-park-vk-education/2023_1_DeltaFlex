#pragma once
#include "MainMenuButton.hpp"
#include "MainMenuCheckBox.hpp"
#include "MainMenuSlider.hpp"

class OptionsNextButton : public MainMenuButton
{
public:
    void onClick()
    {
        std::cout << "SEREGA GDE EDITOR\n";
    }
};

class OptionsPrevButton : public MainMenuButton
{
public:
    void onClick()
    {
        DFEngine::Instance->SwitchScene("default");
    }
};

class OptionsMusicCB : public MainMenuCheckBox
{
public:
    void onClick()
    {
        MainMenuCheckBox::onClick();
    }
};

class OptionsMusicSlider : public MainMenuSlider
{
public:
    void onMouseDrag()
    {
        MainMenuSlider::onMouseDrag();   
    }
};
