#pragma once

#include <DFEntity.hpp>
#include <DFEngine.hpp>
#include <DFComponent.hpp>
#include <DFInputSystem.hpp>

#include <string>
#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define ButtonsAmount 3

class StickmanQuery : public DFComponent
{
public:
    friend class BattleController;
    std::string m_message_path;
    Vector2<float> draw_position;

public:
    void onInit(DFEntity &gameObject)
    {
        draw_position = gameObject.transform.position;
        parent_position = &(gameObject.transform.position);
    }

    void onRenderTextures(DFRenderSystem &render_system)
    {
        m_tex_message = render_system.CreateTextureFromFile(m_message_path);
    }

    void Start()
    {
    }

    void Update()
    {
    }

    void Draw(DFRenderSystem &render_system)
    {
        render_system.RenderTextureUI(m_tex_message, *parent_position);
    }
    
    void Toggle()
    {
        is_visible = !is_visible;
        if (is_visible)
        {
            *parent_position = draw_position;
        }
        else
        {
            parent_position->y = -500;
        }
    }

private:
    DFTexture m_tex_message;
    bool is_visible;
    Vector2<float> *parent_position;
};
