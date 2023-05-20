#pragma once

#include <DFEntity.hpp>
#include <DFComponent.hpp>
#include <DFInputSystem.hpp>

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class MainMenuButton: public DFComponent
{
public:
    std::string img_path;
    Vector2<float> halign;

    void onInit(DFEntity &gameObject);

    void onRenderTextures(DFScUpdParams_t &render_data);

    void Start();

    void Update();

    void Draw(DFScUpdParams_t &render_data);

    virtual void onClick()
    {
        // std::cout << "nigger\n";
        // DFEngine::Instance->SwitchScene("game");
    }

private:
    void CheckMouseBounds();
    SDL_Texture *m_tex;
    Vector2<float> *m_gameObjPos;
    bool is_active;
};