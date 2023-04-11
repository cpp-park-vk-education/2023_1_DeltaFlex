#pragma once

#include <cstdint>

#include <DFComponent.hpp>
#include <DFvec2.hpp>

class DFCollider: public DFComponent
{
public:
    DFvec2<float> &target_position;
    DFvec2<float> min, max, halign;
    uint16_t layerMask;

    DFCollider(DFvec2<float> &_target_position, DFvec2<float> halign_, uint16_t layer);

    void UpdatePosition();

    bool isMouseHovered();
    bool isIntersection(uint16_t layerMask);
    
    bool isIntersection(DFCollider &other);
};