#pragma once

#include <DFComponent.hpp>
#include <DFWorldScene.hpp>
#include <DFInputSystem.hpp>

#include "PhysicsComponent.hpp"
#include "ControlComponents.hpp"
#include "StickmanQuery.hpp"

#include <iostream>
class BattleController : public DFComponent
{
public:
    std::string stickman_query_component_name = "StickmanQuery";

public:
    void Update()
    {
        Uint64 current_time = DFEngine::GetTime();
        if (!m_stickman_query_comp->is_visible && s_start_time + s_timeframe <= current_time)
        {
            s_start_time = current_time;
            m_stickman_query_comp->Toggle();
        }

        if (DFInputSystem::GetKeyDown(KeyCode::KEYCODE_ESCAPE))
        {
            StickmanPhysicsComponent::SetActiveSim(false);
            StickmanAI::setActiveSim(false);
        }
    }

    void Start()
    {
        s_start_time = DFEngine::GetTime();
        m_stickman_query_comp = DFEntity::Find(stickman_query_component_name)->getComponent<StickmanQuery>();
    }

    void onRenderTextures(DFRenderSystem &render_system)
    {
        m_tex_game_bg = render_system.CreateTextureFromFile("./resources/images/level_temple.png");
        m_tex_game_bg.width = 2280;
        m_tex_game_bg.height = 720;
    }

    void Draw(DFRenderSystem &render_system)
    {
        render_system.RenderTexture(m_tex_game_bg, { 0, 0 });
    }

    void SetQueryComponentRef(StickmanQuery *const comp)
    {
        m_stickman_query_comp = comp;
    }
    
private:
    DFTexture m_tex_game_bg;
    StickmanQuery *m_stickman_query_comp;
    static Uint64 s_start_time;
    static constexpr Uint64 s_timeframe = 30 * 100;
};

Uint64 BattleController::s_start_time;
