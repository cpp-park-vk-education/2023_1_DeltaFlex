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

class MainMenuBack : public DFComponent
{
public:
    std::string img_path;
    std::string logo_path = "./resources/images/menu-logo.png";

    void onInit(DFEntity &gameObject)
    {
        menu_music = std::move(DFMusicFile("./resources/music/main-menu.mp3"));
    }

    void onRenderTextures(DFRenderSystem &render_system)
    {
        game_ver = render_system.CreateTextureText(
            "build: " __TIMESTAMP__,
            "./resources/fonts/corruptor.clean-ldr-regular.ttf",
            15,
            { 255, 255, 255, 0 });
        tex = render_system.CreateTextureFromFile(img_path);
        logo_tex = render_system.CreateTextureFromFile(logo_path);
    }

    void Start()
    {
        DFAudioManager::PlayMusic(menu_music, -1);
        counter = 0;
    }

    void Update()
    {
        counter += DFEngine::deltaTime * M_PI_2;
        logo_y_align = sin(counter) * 15;
        if (counter > M_PI * 2)
        {
            counter -= M_PI * 2;
        }
    }

    void Draw(DFRenderSystem &render_system)
    {
        render_system.RenderTextureUI(tex, {0,0});
        render_system.RenderTextureUI(logo_tex,
            {
                1280 / 2 - 650 / 2,
                720 / 6 + logo_y_align - 220 / 2
            });
        render_system.RenderTextureUI(game_ver, {700, 700});
    }

private:
    DFTexture tex, logo_tex, game_ver;
    float counter, logo_y_align;
    DFMusicFile menu_music;
};
