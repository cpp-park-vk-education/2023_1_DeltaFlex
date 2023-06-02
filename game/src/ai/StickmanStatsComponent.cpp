#include "../../include/ai/StickmanStatsComponent.hpp"
#include "StickmanStatsComponent.hpp"

void StickmanStats::onInit(DFEntity &gameObject)
{
    m_health = StickmanHP::max * 10;
    m_stamina = StickmanHP::max;
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

const int *StickmanStats::getStamina() const
{
    return &m_stamina;
}
