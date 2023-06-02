#pragma once

#include <DFEntity.hpp>
#include <DFComponent.hpp>
#include <DFInputSystem.hpp>

#include <string>
#include <iostream>
#include <cassert>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RestartGameButton.hpp"

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
        m_restart_btn = DFEntity::Find("GameStopper")->getComponent<RestartGameButton>();
        m_exit_btn = DFEntity::Find("GameStopper")->getComponent<ExitGameButton>();
    }

    void Update()
    {
        if (ptr->winner != NOONE)
        {
            m_restart_btn->SetShift({ 640, 500 });
            m_exit_btn->SetShift({ 640, 600 });
        }
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

    // void SetRestartButtonComponent(RestartGameButton *btn)
    // {
    //     m_restart_btn = btn;
    // }

protected:
    DFTexture m_tex_playerwin, m_tex_nnwin;
    RestartGameButton *m_restart_btn;
    ExitGameButton *m_exit_btn;
    Winner_t winner;
    static GameStopper *ptr;
};
