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

class TestAbober: public DFComponent
{
private:
    // DFTransform *transform;
    StickmanPhysicsComponent *comp;

public:
    void onInit(DFEntity &gameObject)
    {
        comp = gameObject.getComponent<StickmanPhysicsComponent>();
    }

    void Update()
    {
        comp->m_stickmanCircles[0]->m_attachedPointMass->m_pos.x += Input::GetAxis(AXIS_HORIZONTAL) * 10;
        comp->m_stickmanCircles[0]->m_attachedPointMass->m_pos.y += Input::GetAxis(AXIS_VERTICAL) * 10;
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


    for(size_t i = 0; i < 200; ++i)
    {
        DFEntity &stickman = sc->addNewObject();
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.addComponent(new TestAbober());
        stickman.transform.position.x += 5 * i;
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
    spdlog::set_level(spdlog::level::trace);
    std::unique_ptr<DFEngine> engine = std::make_unique<DFEngine>();
    engine->AppendSceneAllocator("default", default_scene);

    engine->EngineInit();
    engine->EngineCycle();
}
