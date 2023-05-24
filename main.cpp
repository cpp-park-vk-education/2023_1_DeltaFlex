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
#include "game/include/game_ui/GameActiveSkill.hpp"
#include "game/include/game_ui/GameHealthBar.hpp"
#include "game/include/game_ui/GameStaminaBar.hpp"
#include "game/include/ai/StickmanStatsComponent.hpp"

#include "game/include/SatCollider.hpp"

DFScene *default_scene(void)
{
    DFWorldScene *sc = new DFWorldScene();
    DFEntity &tmp = sc->addNewObject("BattleController");
    tmp.addComponent(new BattleController());
    tmp.onInit();

    std::vector<DFEntity *> stickmans;
    for (int i = 0; i < 2; i++)
    {
        DFEntity &stickman = sc->addNewObject("stickman_" + std::to_string(i));
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.addComponent(new StickmanRestarter());
        stickman.addComponent(new StickmanAI());
        stickman.addComponent(new StickmanPlayer());
        stickman.addComponent(new StickmanStats());
        stickmans.push_back(&stickman);
        // stickman.transform.position.x = 50;
        // stickman.transform.position.y = 50;
        stickman.onInit();
        // std::cout << "after construction" << &stickman;
    }

    {
        DFEntity &t = sc->addNewObject("skibidi");
        t.addComponent(new TestRect());
        t.onInit();
    }

    DFEntity &era = sc->addNewObject("era");
    era.addComponent(new EraComponent(stickmans));
    era.onInit();

    DFEntity &my_hp_me = sc->addNewObject("MyHealthBar");
    my_hp_me.addComponent(new GameHealthBar());
    auto *my_hp_me_comp = my_hp_me.getComponent<GameHealthBar>();
    my_hp_me_comp->halign = { 390 / 2, 40 / 2 };
    my_hp_me.transform.position = { 250, 50 };
    my_hp_me_comp->right_icon_place = false;
    my_hp_me.onInit();

    DFEntity &my_hp_enemy = sc->addNewObject("EnemyHealthBar");
    my_hp_enemy.addComponent(new GameHealthBar());
    auto *enemy_hp_comp = my_hp_enemy.getComponent<GameHealthBar>();
    enemy_hp_comp->halign = { 390 / 2, 40 / 2 };
    my_hp_enemy.transform.position = { 1280 - 250, 50 };
    enemy_hp_comp->right_icon_place = true;
    my_hp_enemy.onInit();

    DFEntity &my_sp = sc->addNewObject("MyStaminaBar");
    my_sp.addComponent(new GameStaminaBar());
    auto *my_sp_comp = my_sp.getComponent<GameStaminaBar>();
    my_sp_comp->halign = { 390 / 2, 40 / 2 };
    my_sp.transform.position = { 250, 2 * 50 };
    my_sp_comp->right_icon_place = false;
    my_sp.onInit();

    DFEntity &my_sp_enemy = sc->addNewObject("EnemyHealthBar");
    my_sp_enemy.addComponent(new GameStaminaBar());
    auto *enemy_sp_comp = my_sp_enemy.getComponent<GameStaminaBar>();
    enemy_sp_comp->halign = { 390 / 2, 40 / 2 };
    my_sp_enemy.transform.position = { 1280 - 250, 2 * 50 };
    enemy_sp_comp->right_icon_place = true;
    my_sp_enemy.onInit();

    DFEntity &active_skill_up = sc->addNewObject("ActiveSkillUp");
    active_skill_up.addComponent(new GameActiveSkill());
    auto *active_skill_up_comp = active_skill_up.getComponent<GameActiveSkill>();
    active_skill_up.transform.position = { 460, 25 };
    active_skill_up_comp->is_up_skill = true;
    active_skill_up.onInit();

    DFEntity &active_skill_down = sc->addNewObject("ActiveSkillDown");
    active_skill_down.addComponent(new GameActiveSkill());
    auto *active_skill_down_comp = active_skill_down.getComponent<GameActiveSkill>();
    active_skill_down.transform.position = { 645, 25 };
    active_skill_down_comp->is_up_skill = false;
    active_skill_down.onInit();

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
    tmp4->halign_line = { 512 / 2, 5 / 2 };
    tmp4->img_path_slider = "./resources/images/menu-slider-slider.png";
    tmp4->halign_slider = { 20 / 2, 50 / 2 };
    slider.onInit();

    return sc;
}

int main(void)
{
    // setlocale(LC_ALL, "rus");
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
