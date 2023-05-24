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
#include "PlayerControl.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <array>
#include <random>
#include <MainMenuBack.hpp>
#include <BattleController.hpp>

#include "PlayerControl.hpp"
#include "game/include/options_volume/OptionsVolumeBack.hpp"
#include "game/include/options_volume/OptionsVolumeControl.hpp"

#include "game/include/SatCollider.hpp"
class TestRect : public DFComponent
{
public:
    Vector2<float> p1, p2;

    SATCollider m_collider;
    TestRect() : m_collider(p1, p2) {}

    void Update()
    {
        Vector2<float> mpos(Input::GetMouseX(), Input::GetMouseY());
        p1 = mpos - Vector2<float>{10, 0};
        p2 = mpos + Vector2<float>{10, 0};
        m_collider.RecalcPoints(5);
    }
    void Draw(DFRenderSystem &render_system)
    {
        if (DFEntity::Find("stickman_0")->getComponent<StickmanPhysicsComponent>()->CheckCollision(m_collider))
        {
            render_system.SetColor(255, 0, 0);
        }
        m_collider.Draw(render_system);
        render_system.SetColor(0, 0, 0);

    }
};

DFScene *default_scene(void)
{
    DFWorldScene *sc = new DFWorldScene();
    DFEntity &tmp = sc->addNewObject("BattleController");
    tmp.addComponent(new BattleController());
    tmp.onInit();
    std::vector<DFEntity *> stickmans;
    for (int i = 0; i < 1; i++)
    {
        DFEntity &stickman = sc->addNewObject("stickman_" + std::to_string(i));
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.addComponent(new StickmanRestarter());
        stickman.addComponent(new StickmanAI());
        stickman.addComponent(new StickmanPlayer());
        stickmans.push_back(&stickman);
        stickman.onInit();
    }

    {
        DFEntity &t = sc->addNewObject("skibidi");
        t.addComponent(new TestRect());
        t.onInit();
    }

    return sc;
}

DFScene *evo_scene(void)
{
    DFWorldScene *sc = new DFWorldScene();
    DFEntity &tmp = sc->addNewObject("BattleController");
    tmp.addComponent(new BattleController());
    tmp.onInit();
    std::vector<DFEntity *> stickmans;
    for (int i = 0; i < 1; i++)
    {
        DFEntity &stickman = sc->addNewObject("stickman_" + std::to_string(i));
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.addComponent(new StickmanRestarter());
        stickman.addComponent(new StickmanAI());
        stickman.addComponent(new StickmanPlayer());
        stickmans.push_back(&stickman);
        stickman.onInit();
    }

    {
        DFEntity &t = sc->addNewObject("skibidi");
        t.addComponent(new TestRect());
        t.onInit();
    }

    DFEntity &era = sc->addNewObject("era");
    era.addComponent(new EraComponent(stickmans));
    era.onInit();

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

    // кнопка перемещения на следующий экран
    DFEntity &next_button = sc->addNewObject("OptionsButtonNext");
    next_button.transform.position = { 1280 - 245 / 2 - 10, 720 - 71 };
    next_button.addComponent(new OptionsNextButton());
    auto *tmp = next_button.getComponent<OptionsNextButton>();
    tmp->img_path = "./resources/images/menu-next-button.png";
    tmp->halign = { 245 / 2, 61 / 2 };
    next_button.onInit();

    // кнопка перемещения на предыдущий экран
    DFEntity &prev_button = sc->addNewObject("OptionsButtonPrev");
    prev_button.transform.position = { 266 / 2 + 20, 720 - 73 };
    prev_button.addComponent(new OptionsPrevButton());
    auto *tmp2 = prev_button.getComponent<OptionsPrevButton>();
    tmp2->img_path = "./resources/images/menu-back-button.png";
    tmp2->halign = { 266 / 2, 63 / 2 };
    prev_button.onInit();

    // // чек боксы
    // DFEntity &cb = sc->addNewObject("OptionsMusicCB");
    // cb.transform.position = { 500, 500 };
    // cb.addComponent(new OptionsMusicCB());
    // auto *tmp3 = cb.getComponent<OptionsMusicCB>();
    // tmp3->img_path_body = "./resources/images/menu-checkbox-unchecked.png";
    // tmp3->img_path_tick = "./resources/images/menu-checkbox-check.png";
    // tmp3->halign = {40 / 2, 40 / 2};
    // cb.onInit();

    // слайдеры
    DFEntity &slider = sc->addNewObject("OptionsMusicSlider");
    slider.transform.position = { 800, 470 };
    slider.addComponent(new OptionsMusicSlider());
    auto *tmp4 = slider.getComponent<OptionsMusicSlider>();
    tmp4->img_path_line = "./resources/images/menu-slider-line.png";
    tmp4->halign_line = { 500 / 2, 5 / 2 };
    tmp4->img_path_slider = "./resources/images/menu-slider-slider.png";
    tmp4->halign_slider = { 20 / 2, 50 / 2 };
    slider.onInit();

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
