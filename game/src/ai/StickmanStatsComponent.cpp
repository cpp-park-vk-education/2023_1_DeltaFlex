#include "../../include/ai/StickmanStatsComponent.hpp"
#include "StickmanStatsComponent.hpp"

void StickmanStats::onInit(DFEntity &gameObject)
{
    m_health = StickmanHP::max;
    m_stamina = 0;
}

void StickmanStats::Update()
{
}

void StickmanStats::applyDamage(int damage)
{
    m_health = std::max(StickmanHP::min, m_health - damage);
}

const int *StickmanStats::getHP() const 
{
    return &m_health;
}

int StickmanStats::getStamina() const 
{
    return m_stamina;
}
