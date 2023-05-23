#pragma once

#include <DFEntity.hpp>
#include <DFComponent.hpp>
#include <DFInputSystem.hpp>

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class MainMenuSlider : public DFComponent
{
public:
    std::string img_path_line;
    std::string img_path_slider;

    Vector2<float> halign_line;
    Vector2<float> halign_slider;

public:
    void onInit(DFEntity &gameObject);
    void onRenderTextures(DFRenderSystem &render_system);
    void Start();
    void Update();
    void Draw(DFRenderSystem &render_system);
    virtual void onMouseDrag();
    int getValue() const;

private:
    void CheckMouseBounds();
    bool GetMouseMoved();

private:
    bool is_active;
    bool is_dragged;

    int m_start, m_end;

    int m_pos;
    static constexpr std::pair<int, int> s_map_range{0, 100}; 

    SDL_Texture *m_tex_line, *m_tex_slider;
    Vector2<float> *m_gameObjPos;
    Vector2<float> m_mouse_pos;
};
