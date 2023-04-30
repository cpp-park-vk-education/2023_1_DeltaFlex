#include <DFInputSystem.hpp>
#include <DFScene.hpp>
#include <DFWorldScene.hpp>
#include <DFEngine.hpp>
#include <DFComponent.hpp>
#include <spdlog/spdlog.h>
#include <DFTransform.hpp>
// #include <DFPosition.hpp>
// #include <DFSprite.hpp>
// #include <DFCollider.hpp>
#include "PhysicsComponent.hpp"

#include <SDL2/SDL.h>
#include <string>

class StickmanRestarter: public DFComponent
{
private:
    StickmanPhysicsComponent *my_stickman;

public:
    void onInit(DFEntity &gameObject)
    {
        my_stickman = gameObject.getComponent<StickmanPhysicsComponent>();
    }

    void Update()
    {
        if (Input::GetKeyDown(KEYCODE_R))
            RestartStickman();
    }

    void RestartStickman()
    {
        // std::cout << "Nigger\n";
        Vector2<float> align(0, 475.873 - 20);
        // std::cout << my_stickman->m_stickmanCircles.size();
        my_stickman->m_pointMasses[0]->m_pos = align + Vector2<float>(619.665, 23.703);
        my_stickman->m_pointMasses[1]->m_pos = align + Vector2<float>(619.665, 43.6235);
        my_stickman->m_pointMasses[2]->m_pos = align + Vector2<float>(619.659, 137.391);
        my_stickman->m_pointMasses[3]->m_pos = align + Vector2<float>(619.63, 83.7396);
        my_stickman->m_pointMasses[4]->m_pos = align + Vector2<float>(619.669, 83.7609);
        my_stickman->m_pointMasses[5]->m_pos = align + Vector2<float>(619.554, 137.073);
        my_stickman->m_pointMasses[6]->m_pos = align + Vector2<float>(619.664, 137.094);
        my_stickman->m_pointMasses[7]->m_pos = align + Vector2<float>(619.704, 190.655);
        my_stickman->m_pointMasses[8]->m_pos = align + Vector2<float>(619.614, 190.794);
        my_stickman->m_pointMasses[9]->m_pos = align + Vector2<float>(619.774, 243.988);
        my_stickman->m_pointMasses[10]->m_pos = align + Vector2<float>(619.544, 244.127);
        for (auto &x : my_stickman->m_pointMasses)
        {
            x->m_acceleration = { 0, 0 };
            x->m_oldPos = x->m_pos;
        }
    }
};
class TestAbober: public DFComponent
{
private:
    // DFTransform *transform;
    std::vector<StickmanPhysicsComponent *> stickmans_physics;
    std::vector<StickmanRestarter *> stickmans_restarters;

public:
    void Start()
    {
        stickmans_physics.reserve(10);
        stickmans_restarters.reserve(10);
        for (size_t i = 0; i < 1; ++i)
        {
            stickmans_physics[i] = DFEntity::Find("stickman_" + std::to_string(i))->getComponent<StickmanPhysicsComponent>();
            stickmans_restarters[i] = DFEntity::Find("stickman_" + std::to_string(i))->getComponent<StickmanRestarter>();
        }
    }

    void Update()
    {
        // std::cout << stickmans[0]<< std::endl;
        // comp->m_stickmanCircles[0]->m_attachedPointMass->m_pos.x += Input::GetAxis(AXIS_HORIZONTAL) * 10;
        StickmanCircle *left = stickmans_physics[0]->m_stickmanCircles[0].get();
        left->m_attachedPointMass->m_pos.x += Input::GetAxis(AXIS_HORIZONTAL) * 10;
        left->m_attachedPointMass->m_pos.y += Input::GetAxis(AXIS_VERTICAL) * 10;

        // stickmans_restarters[0]->RestartStickman();

        // left = comp2->m_stickmanCircles[0];
        // left->m_attachedPointMass->m_pos.x += Input::GetAxis(AXIS_HORIZONTAL) * 10;
        // left->m_attachedPointMass->m_pos.y += Input::GetAxis(AXIS_VERTICAL) * 10;

        // auto &right = comp->m_pointMasses[50-1];
        // right->m_pos.x = Input::GetMouseX();
        // right->m_pos.y = Input::GetMouseY();
    }
};


class TestLine: public DFComponent
{
private:
    DFTransform *transform;

public:
    void onInit(DFEntity &gameObject)
    {
        transform = &gameObject.transform;
    }

    void Update()
    {
        transform->position.x += Input::GetAxis(AXIS_HORIZONTAL);
    }

    void Draw(DFScUpdParams_t &render_data)
    {
        auto *renderer = render_data.renderer.get();
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawLineF(renderer, transform->position.x, transform->position.y, 100, 100);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }
};

DFScene *default_scene(void)
{
    DFWorldScene *sc = new DFWorldScene();


    {
        DFEntity &stickman = sc->addNewObject("stickman_0");
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.addComponent(new StickmanRestarter());
        stickman.transform.position.x = 50;
        stickman.transform.position.y = 50;
        stickman.onInit();
        // std::cout << "after construction" << &stickman;
    }

    {
        DFEntity &stickman = sc->addNewObject("controller");
        stickman.addComponent(new TestAbober());
        stickman.onInit();
    }

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

    // spdlog::set_level(spdlog::level::trace);
    // std::unique_ptr<DFEngine> engine = std::make_unique<DFEngine>();

    // engine->AppendSceneAllocator("default", default_scene);

    // engine->EngineInit();
    // engine->EngineCycle();

    auto test = default_scene();
    delete test;
}
