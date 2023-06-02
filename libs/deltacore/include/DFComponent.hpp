#pragma once
#include <DFScUpdParams.hpp>
// #include <DFEngine.hpp>
// #include <DFEntity.hpp>
#include <cstdlib>
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
    virtual void onRenderTextures(DFRenderSystem &render_system) {}
    virtual void Start() {}
    virtual void Update() {}
    virtual void Draw(DFRenderSystem &render_system) {}
    virtual ~DFComponent() = default;

#ifdef EXPERIMENTAL_ALLOCATOR
    void *operator new(std::size_t count);
    void operator delete(void *pointer);
#endif
};
