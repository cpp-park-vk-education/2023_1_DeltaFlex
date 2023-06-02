#pragma once

#include <DFEntity.hpp>
#include <DFComponent.hpp>
#include <DFInputSystem.hpp>

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../UiButton.hpp"
#include "../StickmanQuery.hpp"
#include "../ai/ControlComponents.hpp"

class StickmanQueryButton : public UiButton
{
public:
    std::string icon_path;

public:
    void onRenderTextures(DFRenderSystem &render_system)
    {
        UiButton::onRenderTextures(render_system);

        m_icon = render_system.CreateTextureFromFile(icon_path);
        m_icon.width = 50;
        m_icon.height = 50;
    }

    void Draw(DFRenderSystem &render_system)
    {
        Vector2<float> pos =
        {
            UiButton::m_gameObjPos->x - UiButton::halign.x + UiButton::shift.x + 10 * UiButton::is_active,
            UiButton::m_gameObjPos->y - UiButton::halign.y + UiButton::shift.y + 10 * UiButton::is_active,
        };
        render_system.RenderTextureUI(UiButton::m_tex, pos);

        Vector2<float> icon_pos = 
        {
            pos.x + 33,
            pos.y + 10
        };
        render_system.RenderTextureUI(m_icon, icon_pos);
    }

    void onClick()
    {
        assert(m_sq != nullptr);
        m_sq->Toggle();
    }

    void SetStickmanQuery(StickmanQuery *sq)
    {
        m_sq = sq;
    }

protected:
    DFTexture m_icon;
    StickmanQuery *m_sq;
};


class StickmanQueryButtonAttack : public StickmanQueryButton
{
public:
    void onClick()
    {
        StickmanQueryButton::onClick();
        auto stickman = DFEntity::Find("stickman_1")->getComponent<StickmanAI>();
        stickman->training_model = 1;
        stickman->training_time = 300;
    }
};

class StickmanQueryButtonIdle : public StickmanQueryButton
{
public:
    void onClick()
    {
        StickmanQueryButton::onClick();
        auto stickman = DFEntity::Find("stickman_1")->getComponent<StickmanAI>();
        stickman->training_model = 0;
        stickman->training_time = 300;
    }
};

class StickmanQueryButtonProtect : public StickmanQueryButton
{
public:
    void onClick()
    {
        StickmanQueryButton::onClick();
        auto stickman = DFEntity::Find("stickman_1")->getComponent<StickmanAI>();
        stickman->training_model = 2;
        stickman->training_time = 300;
    }
};
