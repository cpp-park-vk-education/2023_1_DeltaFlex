#pragma once

#include <DFEntity.hpp>
#include <DFComponent.hpp>
#include <DFInputSystem.hpp>

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../UiButton.hpp"
#include "../ai/ControlComponents.hpp"
#include "../physics/PhysicsComponent.hpp"

class RestartGameButton : public UiButton
{
public:
    void onInit(DFEntity &gameObject)
    {
        UiButton::onInit(gameObject);
        img_path = "./resources/images/game-restart.png";
    }

    void Start()
    {
        UiButton::Start();
        shift = {-500, 0};
    }

    void onRenderTextures(DFRenderSystem &render_system)
    {
        UiButton::onRenderTextures(render_system);
        m_tex.width /= 2;
        m_tex.height /= 2;
        halign = {(double)m_tex.width / 2., (double)m_tex.height / 2.};
    }

    void onClick()
    {
        DFEngine::Instance->SwitchScene("game");
        StickmanPhysicsComponent::SetActiveSim(true);
        StickmanAI::setActiveSim(true);
    }

    void SetShift(const Vector2<float> s)
    {
        shift = s;
    }

};


class ExitGameButton : public UiButton
{
public:
    void onInit(DFEntity &gameObject)
    {
        UiButton::onInit(gameObject);
        img_path = "./resources/images/game-exit.png";
    }

    void Start()
    {
        UiButton::Start();
        shift = {-500, 0};
    }

    void onRenderTextures(DFRenderSystem &render_system)
    {
        UiButton::onRenderTextures(render_system);
        m_tex.width /= 2;
        m_tex.height /= 2;
        halign = {(double)m_tex.width / 2., (double)m_tex.height / 2.};
    }

    void onClick()
    {
        StickmanPhysicsComponent::SetActiveSim(true);
        StickmanAI::setActiveSim(true);
        DFEngine::Instance->SwitchScene("default");
    }

    void SetShift(const Vector2<float> s)
    {
        shift = s;
    }

};