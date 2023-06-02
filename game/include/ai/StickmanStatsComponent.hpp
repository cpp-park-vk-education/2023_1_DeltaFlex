#pragma once

#include "ControlComponents.hpp"
#include "DFComponent.hpp"
#include "DFEntity.hpp"
#include "DFInputSystem.hpp"
class StickmanAI;
class StickmanStats : public DFComponent
{
public:
    void onInit(DFEntity &gameObject);
    void Update();
    void applyDamage(int damage);
    const int *getHP() const;
    const int *getStamina() const;

private:
    int m_health;
    int m_stamina;
    StickmanAI *my_stickman;

private:
    struct StickmanHP
    {
        static constexpr int min = 0;
        static constexpr int max = 100;
    };
};
