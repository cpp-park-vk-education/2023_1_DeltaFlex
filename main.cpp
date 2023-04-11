#include <DFInputSystem.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <DFEngine.hpp>
#include <DFEntity.hpp>
#include <spdlog/spdlog.h>

#include <DFPosition.hpp>
#include <DFSprite.hpp>
#include <DFCollider.hpp>

#include <SDL2/SDL_mixer.h>

#include <DFAudioManager.hpp>

int main(void)
{
    spdlog::set_level(spdlog::level::trace);
    std::unique_ptr<DFEngine> engine = std::make_unique<DFEngine>();

    engine->EngineInit();
    engine->EngineCycle();
}