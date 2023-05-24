#pragma once

#include <DFEntity.hpp>
#include <DFComponent.hpp>
#include <DFInputSystem.hpp>

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <DFAudioManager.hpp>
#include <cmath>

class OptionsVolumeBack : public DFComponent
{
public:
    std::string bg_path = "./resources/images/options-menu-back.png";
    std::string section_path = "./resources/images/options-menu-volume-text.png";

    void onInit(DFEntity &gameObject)
    {
        menu_music = std::move(DFMusicFile("./resources/music/main-menu.mp3"));
    }
    
    void onRenderTextures(DFRenderSystem &render_system)
    {
        bg_texture = render_system.CreateTextureFromFile(bg_path);
        section_texture = render_system.CreateTextureFromFile(section_path);
    }

    void Start()
    {
    }

    void Update()
    {
    }

    void Draw(DFRenderSystem &render_system)
    {
        render_system.RenderTexture(bg_texture, NULL, NULL);
        render_system.RenderTexture(section_texture, NULL, NULL);
    }

private:
    DFTexture bg_texture, section_texture;
    DFMusicFile menu_music;
};
