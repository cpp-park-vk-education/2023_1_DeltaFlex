#pragma once

#include <DFEntity.hpp>
#include <DFComponent.hpp>
#include <DFInputSystem.hpp>

#include <string>
#include <iostream>
#include <cassert>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameStopper : public DFComponent
{
public:
    std::string tex_player_win_path = "./resources/images/player-victory-dark.png";
    std::string tex_nn_win_path = "./resources/images/nn-victory-dark.png";

protected:
    enum Winner_t { PLAYER, NNETWORK, NOONE };

public:
    GameStopper()
    {
        ptr = this;
    }

    void onInit(DFEntity &gameObject)
    {
        ptr->winner = NOONE;
    }

    void onRenderTextures(DFRenderSystem &render_system)
    {
        m_tex_playerwin = render_system.CreateTextureFromFile(tex_player_win_path);
        m_tex_nnwin = render_system.CreateTextureFromFile(tex_nn_win_path);
    }

    void Start()
    {
    }

    void Update()
    {
    }

    void Draw(DFRenderSystem &render_system)
    {
        if (ptr->winner == PLAYER)
            render_system.RenderTextureUI(m_tex_playerwin, { 0, 0 });
        else if (ptr->winner == NNETWORK)
            render_system.RenderTextureUI(m_tex_nnwin, { 0, 0 });
    }

    static void SetPlayerWon() noexcept
    {
        if (ptr->winner == NOONE)
            ptr->winner = PLAYER;
    }

    static void SetNNWon() noexcept
    {
        if (ptr->winner == NOONE)
            ptr->winner = NNETWORK;
    }

protected:
    DFTexture m_tex_playerwin, m_tex_nnwin;
    Winner_t winner;
    static GameStopper *ptr;
};
