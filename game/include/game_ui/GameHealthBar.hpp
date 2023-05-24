#pragma once

#include <DFEntity.hpp>
#include <DFComponent.hpp>
#include <DFInputSystem.hpp>

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameHealthBar: public DFComponent
{
public:
    Vector2<float> halign;
    const int *current_health;

public:
    void onInit(DFEntity &gameObject);
    void onRenderTextures(DFRenderSystem &render_system);
    void Start();
    void Update();
    void Draw(DFRenderSystem &render_system);

private:
    Vector2<float> *m_game_object_pos;
    
    static int m_margin;
    static int m_thickness;
};
