#pragma once

#include <DFComponent.hpp>
#include <DFWorldScene.hpp>
#include <DFInputSystem.hpp>

class BattleController : public DFComponent
{
public:
    void onRenderTextures(DFRenderSystem &render_system)
    {
        tex = render_system.CreateTextureFromFile("./resources/images/level_temple.png");
        tex.width = 2280;
        tex.height = 720;
    }

    void Draw(DFRenderSystem &render_system)
    {
        render_system.RenderTexture(tex, { 0, 0 });
    }
    
private:
    DFTexture tex;
};
