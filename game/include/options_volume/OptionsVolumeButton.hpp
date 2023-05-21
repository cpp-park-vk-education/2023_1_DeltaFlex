#pragma once
#include "MainMenuButton.hpp"

class OptionsNextButton : public MainMenuButton
{
public:
    void onClick()
    {
        std::cout << "SEREGA GDE EDITOR\n";
    }
};
