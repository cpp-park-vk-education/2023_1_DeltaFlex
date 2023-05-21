#pragma once

#include <vector>

#include <DFScUpdParams.hpp>
#include <DFCollider.hpp>
#include <DFRenderSystem.hpp>
// #include <DFEntity.hpp>

class DFEntity;

class DFScene
{
public:
    virtual void onRenderTextures(DFRenderSystem &render_system) = 0;
    virtual void onSceneStart(DFRenderSystem &render_system) = 0;
    virtual void onHandleFrame(DFRenderSystem &render_system) = 0;

    virtual DFEntity *findEntity(std::string &name) { return nullptr; }

    virtual bool isIntersection(DFCollider &collider, uint16_t layerMask) { return false; }
    virtual DFEntity *firstIntersection(DFCollider &collider, uint16_t layerMask) { return nullptr; }
    virtual std::vector<DFEntity *> allIntersection(DFCollider &collider, uint16_t layerMask) { return std::vector<DFEntity *>(); }

    virtual ~DFScene() = default;
};

using scene_allocator_t = DFScene * (*)(void);