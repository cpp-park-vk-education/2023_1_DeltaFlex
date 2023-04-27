#include <DFCollider.hpp>

#include <cstdint>
#include <DFInputSystem.hpp>

DFCollider::DFCollider(Vector2<float> &_target_position, Vector2<float> halign_, uint16_t layer):
    target_position(_target_position),
    halign(halign_),
    layerMask(layer)
{
    UpdatePosition();
}

void DFCollider::UpdatePosition() {
    max = target_position + halign;
    min = target_position - halign;
}

bool DFCollider::isMouseHovered()
{
    int m_x = Input::GetMouseX(), m_y = Input::GetMouseY();
    if (min.x > m_x || max.x < m_x) return false;
    if (min.y > m_y || max.y < m_y) return false;

    return true;
}

bool DFCollider::isIntersection(uint16_t layerMask)
{
    UpdatePosition();
    return DFEngine::GetActiveScene()->isIntersection(*this, layerMask);
}

bool DFCollider::isIntersection(DFCollider &other)
{
    if (max.x < other.min.x || min.x > other.max.x) return false;
    if (max.y < other.min.y || min.y > other.max.y) return false;

    return true;
}