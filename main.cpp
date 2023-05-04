#include <DFInputSystem.hpp>
#include <DFScene.hpp>
#include <DFWorldScene.hpp>
#include <DFEngine.hpp>
#include <DFComponent.hpp>
#include <spdlog/spdlog.h>
#include <DFTransform.hpp>
#include <iomanip>
// #include <DFPosition.hpp>
// #include <DFSprite.hpp>
// #include <DFCollider.hpp>
#include "PhysicsComponent.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <array>
#include <random>

// class TestAbober: public DFComponent
// {
// private:
//     // DFTransform *transform;
//     std::vector<StickmanPhysicsComponent *> stickmans_physics;
//     std::vector<StickmanRestarter *> stickmans_restarters;

// public:
//     void Start()
//     {
//         stickmans_physics.reserve(10);
//         stickmans_restarters.reserve(10);
//         for (size_t i = 0; i < 1; ++i)
//         {
//             stickmans_physics[i] = DFEntity::Find("stickman_" + std::to_string(i))->getComponent<StickmanPhysicsComponent>();
//             stickmans_restarters[i] = DFEntity::Find("stickman_" + std::to_string(i))->getComponent<StickmanRestarter>();
//         }
//     }

//     void Update()
//     {
//         // std::cout << stickmans[0]<< std::endl;
//         // comp->m_stickmanCircles[0]->m_attachedPointMass->m_pos.x += Input::GetAxis(AXIS_HORIZONTAL) * 10;
//         StickmanCircle *left = stickmans_physics[0]->m_stickmanCircles[0].get();
//         left->m_attachedPointMass->m_pos.x += Input::GetAxis(AXIS_HORIZONTAL) * 10;
//         left->m_attachedPointMass->m_pos.y += Input::GetAxis(AXIS_VERTICAL) * 10;

//         // stickmans_restarters[0]->RestartStickman();

//         // left = comp2->m_stickmanCircles[0];
//         // left->m_attachedPointMass->m_pos.x += Input::GetAxis(AXIS_HORIZONTAL) * 10;
//         // left->m_attachedPointMass->m_pos.y += Input::GetAxis(AXIS_VERTICAL) * 10;

//         // auto &right = comp->m_pointMasses[50-1];
//         // right->m_pos.x = Input::GetMouseX();
//         // right->m_pos.y = Input::GetMouseY();
//     }
// };

DFScene *default_scene(void)
{
    DFWorldScene *sc = new DFWorldScene();
    std::vector<DFEntity*> stickmans;
    for (int i = 0; i < 100; i++)
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

int main(void)
{
    // DFEntity entity;
    // entity.addComponent(new DFSprite("./gears.png", entity.transform));
    // entity.addComponent(new DFCollider(entity.transform.position, Vector2<float>(12, 12), 1));
    // std::cout << entity.getComponent<DFCollider>() << std::endl;
    // entity.addComponent()
    // int a = 4;
    // std::cout << (typeid(int) == typeid(a));

    spdlog::set_level(spdlog::level::trace);
    std::unique_ptr<DFEngine> engine = std::make_unique<DFEngine>();

    engine->AppendSceneAllocator("default", default_scene);

    engine->EngineInit();
    engine->EngineCycle();
}
