#pragma once

#include <DFEntity.hpp>
#include <DFComponent.hpp>
#include <DFInputSystem.hpp>

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameActiveSkill: public DFComponent
{
public:
    bool is_up_skill;
public:
    void onInit(DFEntity &gameObject);
    void onRenderTextures(DFRenderSystem &render_system);
    void Start();
    void Update();
    void Draw(DFRenderSystem &render_system);

private:
    Vector2<float> *m_game_object_pos;
    DFTexture neuron_textures[2];
    DFTexture *m_tex_active, m_tex_one, m_tex_two;

};
