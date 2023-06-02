#pragma once

#include <DFComponent.hpp>
#include <DFWorldScene.hpp>
#include <DFInputSystem.hpp>

#include "PhysicsComponent.hpp"
#include "ControlComponents.hpp"
#include "StickmanQuery.hpp"
#include "GameStopper.hpp"

#include <iostream>
class BattleController : public DFComponent
{
public:
    std::string stickman_query_component_name = "StickmanQuery";

public:

    void Update()
    {
        if (!s_updating)
            return; 

        Uint64 current_time = DFEngine::GetTime();
        if (!m_stickman_query_comp->is_visible && (s_start_time + s_timeframe <= current_time))
        {
            s_start_time = current_time;
            m_stickman_query_comp->Toggle();
        }

        if (DFInputSystem::GetKeyDown(KeyCode::KEYCODE_ESCAPE))
        {
            StickmanPhysicsComponent::SetActiveSim(false);
            StickmanAI::setActiveSim(false);
        }

        if (*m_first_stickman_stat->getHP() == 0 || *m_second_stickman_stat->getHP() == 0)
        {
            s_updating = false;
            m_stickman_query_comp->SetToggled(false);

            StickmanPhysicsComponent::SetActiveSim(false);
            StickmanAI::setActiveSim(false);

            if (*m_first_stickman_stat->getHP() == 0)
            {
                GameStopper::SetPlayerWon();
            }
            else if (*m_second_stickman_stat->getHP() == 0)
            {
                GameStopper::SetNNWon();
            }
        }
    }

    void SetCurrentTime(Uint64 time)
    {
        s_start_time = time;
    }

    void Start()
    {
        s_updating = true;
        s_start_time = DFEngine::GetTime();
        m_stickman_query_comp = DFEntity::Find(stickman_query_component_name)->getComponent<StickmanQuery>();

        m_first_stickman_stat = DFEntity::Find("stickman_0")->getComponent<StickmanStats>();
        m_second_stickman_stat = DFEntity::Find("stickman_1")->getComponent<StickmanStats>();
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
    StickmanStats *m_first_stickman_stat, *m_second_stickman_stat;
    static Uint64 s_start_time;
    static constexpr Uint64 s_timeframe = 10 * 1000;
    static bool s_updating;
};

Uint64 BattleController::s_start_time;
bool BattleController::s_updating;
