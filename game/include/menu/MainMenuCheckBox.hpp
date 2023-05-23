#pragma once

#include <DFEntity.hpp>
#include <DFComponent.hpp>
#include <DFInputSystem.hpp>

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class MainMenuCheckBox: public DFComponent
{
public:
    std::string img_path_body;
    std::string img_path_tick;
    Vector2<float> halign;

public:
    void onInit(DFEntity &gameObject);
    void onRenderTextures(DFRenderSystem &render_system);
    void Start();
    void Update();
    void Draw(DFRenderSystem &render_system);
    virtual void onClick();
    bool isChecked() const;

private:
    void CheckMouseBounds();
    SDL_Texture *m_tex_body, *m_tex_tick;
    Vector2<float> *m_gameObjPos;
    bool m_checked;
    bool is_active;
};
