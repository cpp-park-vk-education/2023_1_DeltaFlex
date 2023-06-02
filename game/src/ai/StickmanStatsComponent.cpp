#include "../../include/ai/StickmanStatsComponent.hpp"
#include "StickmanStatsComponent.hpp"
#include "ControlComponents.hpp"


void StickmanStats::onInit(DFEntity &gameObject)
{
    my_stickman = gameObject.getComponent<StickmanAI>();
    // std::cout << my_stickman;
    m_health = StickmanHP::max * 10;
    m_stamina = StickmanHP::max * 5;
}

void StickmanStats::Update()
{
    int &walk_action = my_stickman->walk_action;
    if (walk_action != 0)
    {
        --m_stamina;
        if (m_stamina < 0)
        {
            m_stamina = 0;
            walk_action = 0;
        }
    }
    else
    {
        m_stamina = std::min(500, m_stamina + 1);
    }
}

void StickmanStats::applyDamage(int damage)
{
    m_health = std::max(StickmanHP::min, m_health - damage);
}

const int *StickmanStats::getHP() const
{
    return &m_health;
}

const int *StickmanStats::getStamina() const
{
    return &m_stamina;
}
