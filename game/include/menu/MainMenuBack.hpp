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
        game_ver_rect.x = 700;
        game_ver_rect.y = 700;
    }

    void onRenderTextures(DFRenderSystem &render_system)
    {
        // ./resources/fonts/sf-mono.otf
        // auto *fnt = TTF_OpenFont("./resources/fonts/corruptor.clean-ldr-regular.ttf", 15);
        // std::cout << TTF_GetError() << "\n";
        // SDL_Color textColor = {255, 255, 255, 0};
        // auto *surf = TTF_RenderText_Solid(fnt, "build: " __TIMESTAMP__, textColor);
        game_ver = render_system.CreateTextureText(
            "build: " __TIMESTAMP__,
            "./resources/fonts/corruptor.clean-ldr-regular.ttf",
            // "./resources/fonts/sf-mono.otf",
            15,
            { 255, 255, 255, 0 });
        // game_ver = SDL_CreateTextureFromSurface(render_data.renderer.get(), surf);
        game_ver_rect.w = game_ver.width;
        game_ver_rect.h = game_ver.height;
        // SDL_FreeSurface(surf);
        // TTF_CloseFont(fnt);
        // std::cout << "load text " << img_path.c_str() << "\n";
        // tex = IMG_LoadTexture(render_data.renderer.get(), img_path.c_str());
        tex = render_system.CreateTextureFromFile(img_path);
        // logo_tex = IMG_LoadTexture(render_data.renderer.get(), logo_path.c_str());
        logo_tex = render_system.CreateTextureFromFile(logo_path);
    }

    void Start()
    {
        DFAudioManager::PlayMusic(menu_music, -1);
        counter = 0;
    }

    void Update()
    {
        counter += DFEngine::deltaTime * M_PI / 2;
        logo_y_align = sin(counter) * 15;
    }

    void Draw(DFRenderSystem &render_system)
    {
        render_system.RenderTexture(tex, NULL, NULL);
        render_system.RenderTexture(logo_tex,
            {
                1280 / 2 - 650 / 2,
                720 / 6 + logo_y_align - 220 / 2
            });
        render_system.RenderTexture(game_ver, {700, 700});
    }

private:
    DFTexture tex, logo_tex, game_ver;
    SDL_Rect game_ver_rect;
    float counter, logo_y_align;
    DFMusicFile menu_music;
};
