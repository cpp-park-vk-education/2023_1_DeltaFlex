#pragma once

#include <DFPosition.hpp>
#include <DFCollider.hpp>
#include <DFScUpdParams.hpp>

class DFEntity
{
public:
    DFPosition position;
    DFCollider collider;

    DFEntity(): position(0, 0), collider(position, DFvec2<float>(0, 0), 0) {}
    DFEntity(DFPosition pos, DFCollider col): position(pos), collider(col) {}
    virtual void onRenderTextures(DFScUpdParams_t &render_data) {};
    virtual void Update() {};
    virtual void Draw(DFScUpdParams_t &render_data) {};
    virtual ~DFEntity() = default;
};