#pragma once
#include <DFScUpdParams.hpp>
// #include <DFEntity.hpp>

#include <memory>

class DFEntity;
class DFComponent
{
public:
    virtual void onInit(DFEntity &gameObject) {}
    virtual void Start() {}
    virtual void Update() {}
    virtual void Draw(DFScUpdParams_t &render_data) {}
    virtual ~DFComponent() = default;
};