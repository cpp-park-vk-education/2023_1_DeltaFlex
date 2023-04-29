#pragma once
#include <DFScUpdParams.hpp>
// #include <DFEntity.hpp>

#include <memory>

class DFEntity;
class DFComponent
{
public:
    // DFComponent() = default;
    // DFComponent(const DFComponent &other) = delete;
    // DFComponent(DFComponent &&other) = delete;

    // DFComponent &operator=(const DFComponent &other) = delete;
    // DFComponent &operator=(DFComponent &&other) = delete;

    virtual void onInit(DFEntity &gameObject) {}
    virtual void Start() {}
    virtual void Update() {}
    virtual void Draw(DFScUpdParams_t &render_data) {}
    virtual ~DFComponent() = default;
};
