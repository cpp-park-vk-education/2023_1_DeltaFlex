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

#include <SDL2/SDL.h>

// #include <DFAudioManager.hpp>

class StickmanBody: public DFComponent
{
private:
    DFTransform *transform;
public:
    void onInit(DFEntity &gameObject)
    {
        transform = &gameObject.transform;
    }

    void Draw(DFScUpdParams_t &render_data)
    {
        SDL_Renderer *p_renderer = render_data.renderer.get();
        SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(p_renderer, transform->position.x, transform->position.y, 100, 100);
        SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);
    }
};

class PlayerControl: public DFComponent
{
private:
    DFTransform *transform;

    double playerSpeed;
public:
    void onInit(DFEntity &gameObject)
    {
        transform = &gameObject.transform;
        playerSpeed = 100;
    }

    void Update()
    {
        transform->position.x += Input::GetAxis(AXIS_HORIZONTAL) * playerSpeed * DFEngine::deltaTime;
        transform->position.y += Input::GetAxis(AXIS_VERTICAL) * playerSpeed * DFEngine::deltaTime;
    }
};

DFScene *default_scene(void)
{
    DFWorldScene *sc = new DFWorldScene();
    DFEntity &stickman = sc->addNewObject();
    stickman.addComponent(new StickmanBody());
    stickman.addComponent(new PlayerControl());
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