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
    std::string img_path_slider;
    Vector2<float> halign;

public:
    void onInit(DFEntity &gameObject);
    void onRenderTextures(DFRenderSystem &render_system);
    void Start();
    void Update();
    void Draw(DFRenderSystem &render_system);
    virtual void onClick();
    int getValue() const;

private:
    void CheckMouseBounds();
    void Map(int value, int min1, int max1, int min2, int max2);

private:
    int m_start, m_end, m_current;
    bool is_active;
    SDL_Texture *m_tex_slider;
    Vector2<float> *m_gameObjPos;
};
