#pragma once

#include "DFComponent.hpp"
#include "DFEntity.hpp"
#include "ControlComponents.hpp"
#include "DFInputSystem.hpp"

class StickmanStats : public DFComponent
{
public:
    void onInit(DFEntity &gameObject);
    void Update();
    void applyDamage(int damage);
    const int *getHP() const;
    int getStamina() const;

private:
    int m_health;
    int m_stamina;

private:
    struct StickmanHP
    {
        static constexpr int min = 0;
        static constexpr int max = 100;
    };
};
