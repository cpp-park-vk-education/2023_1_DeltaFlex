#include <DFSceneLoader.hpp>
#include <DFInputSystem.hpp>
#include <DFScene.hpp>
#include <DFWorldScene.hpp>
#include <DFEngine.hpp>
#include <DFComponent.hpp>
#include <spdlog/spdlog.h>
#include <DFTransform.hpp>
#include <iomanip>
#include <SDL2/SDL_ttf.h>
// #include <DFPosition.hpp>
// #include <DFSprite.hpp>
// #include <DFCollider.hpp>
#include "PhysicsComponent.hpp"

#include "ControlComponents.hpp"
#include "Evolution.hpp"
#include "MatrixActions.hpp"
#include "Model.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <array>
#include <random>
#include <MainMenuBack.hpp>
#include <BattleController.hpp>

#include "game/include/options_volume/OptionsVolumeBack.hpp"
#include "game/include/options_volume/OptionsVolumeButton.hpp"

DFScene *default_scene(void)
{
    DFWorldScene *sc = new DFWorldScene();
    DFEntity &tmp = sc->addNewObject("BattleController");
    tmp.addComponent(new BattleController());
    tmp.onInit();
    std::vector<DFEntity *> stickmans;
    for (int i = 0; i < 200; i++)
    {
        DFEntity &stickman = sc->addNewObject("stickman_" + std::to_string(i));
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.addComponent(new StickmanRestarter());
        stickman.addComponent(new StickmanAI());
        stickmans.push_back(&stickman);
        // stickman.transform.position.x = 50;
        // stickman.transform.position.y = 50;
        stickman.onInit();
        // std::cout << "after construction" << &stickman;
    }

    DFEntity &era = sc->addNewObject("era");
    era.addComponent(new EraComponent(stickmans));
    era.onInit();

    // {
    //     DFEntity &stickman = sc->addNewObject("controller");
    //     stickman.addComponent(new TestAbober());
    //     stickman.onInit();
    // }

    // DFEntity &stickman1 = sc->addNewObject();
    // stickman1.addComponent(new StickmanPhysicsComponent());
    // stickman1.addComponent(new TestAbober());
    // stickman1.onInit();
    // // stickman2.addComponent(new TestAbober());
    // stickman2.getComponent<StickmanPhysicsComponent>()->m_stickmanCircles[0]->m_attachedPointMass->m_pos.x += 300;
    // stickman.addComponent(new PlayerControl());
    return sc;
}

DFScene *menu_scene(void)
{
    DFSceneLoader example("./scenes/test.scene");
    return example.Load();
}

DFScene *options_volume_control(void)
{
    DFWorldScene *sc = new DFWorldScene();
    DFEntity &bg = sc->addNewObject("OptionsVolume");
    bg.addComponent(new OptionsVolumeBack());
    bg.onInit();

    DFEntity &next_button = sc->addNewObject("OptionsButtonNext");
    next_button.transform.position = {1280 - 255, 720 - 71};
    
    next_button.addComponent(new OptionsNextButton());
    auto *tmp = next_button.getComponent<OptionsNextButton>();
    tmp->img_path = "./resources/images/menu-next-button.png";
    tmp->halign = {245 / 2, 61 / 2};

    next_button.onInit();

    return sc;
}

int main(void)
{
    TTF_Init();
    spdlog::set_level(spdlog::level::trace);
    // std::cout << __TIMESTAMP__ << std::endl;

    std::unique_ptr<DFEngine> engine = std::make_unique<DFEngine>();

    engine->AppendSceneAllocator("default", menu_scene);
    engine->AppendSceneAllocator("game", default_scene);
    engine->AppendSceneAllocator("options-volume", options_volume_control);

    engine->EngineInit();
    engine->EngineCycle();
}
