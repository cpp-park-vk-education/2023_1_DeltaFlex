#pragma once

#include <DFComponent.hpp>
#include <DFWorldScene.hpp>
#include <DFInputSystem.hpp>

#include "PhysicsComponent.hpp"
#include "ControlComponents.hpp"

#include <iostream>

class BattleController : public DFComponent
{
public:
    void Update()
    {
        if (DFInputSystem::GetKeyDown(KeyCode::KEYCODE_ESCAPE))
        {
            StickmanPhysicsComponent::SetActiveSim(false);
            StickmanAI::setActiveSim(false);
        }
    }

    void onRenderTextures(DFRenderSystem &render_system)
    {
        tex = render_system.CreateTextureFromFile("./resources/images/level_temple.png");
    }

    void Draw(DFRenderSystem &render_system)
    {
        render_system.RenderTexture(tex, { 0, 0 });
    }
    
private:
    DFTexture tex;
};
