#pragma once

#include <DFComponent.hpp>
#include <DFWorldScene.hpp>
#include <DFInputSystem.hpp>

class BattleController: public DFComponent
{
public:

    void onInit(DFEntity &gameObj)
    {
        pos = &gameObj.transform.position;
    }
    
    void onRenderTextures(DFRenderSystem &render_system)
    {
        tx_rect.x = 0;
        tx_rect.y = 0;
        tx_rect.w = 2280;
        tx_rect.h = 1080;
        tex = render_system.CreateTextureFromFile("./resources/images/level_temple.png");
    }

    void Start()
    {
        auto this_gameobj = DFEntity::Find("BattleController");
        std::cout << "invoke BattleController start" << (void*)this_gameobj << "\n";
        DFEntity::Find("Camera")->getComponent<DFCameraComponent>()->SetTarget(*this_gameobj);
    }

    void Update()
    {
        pos->x += Input::GetAxis(AXIS_HORIZONTAL);
        pos->y += Input::GetAxis(AXIS_VERTICAL);
    }

    void Draw(DFRenderSystem &render_system)
    {
        render_system.RenderTexture(tex, NULL, &tx_rect);

        render_system.RenderCircle(pos->x, pos->y, 10);
    }
private:
    SDL_Texture *tex;
    SDL_Rect tx_rect;
    Vector2<float> *pos;
};