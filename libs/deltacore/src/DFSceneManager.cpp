#include <DFSceneManager.hpp>
#include <DFScene.hpp>
#include <DFEngine.hpp>
#include <spdlog/spdlog.h>
#include <thread>
#include <DFLoadingScene.hpp>

#include <SDL2/SDL_image.h>

DFSceneManager * DFSceneManager::Instance = nullptr;

DFSceneManager::DFSceneManager():
    activeScene(nullptr),
    loadingScreenScene(new DFLoadingScene),
    tmpLoaded(nullptr)
{
    Instance = this;
}

void DFSceneManager::initSceneManager(DFScUpdParams_t &render_data, const char *entrypoint)
{
    loadingScreenScene->onRenderTextures(render_data.render_system);
    SwitchScene(entrypoint);
}

void DFSceneManager::AppendSceneAllocator(std::string key, scene_allocator_t allocator)
{
    scene_allocators_map[key] = allocator;
}

void DFSceneManager::asyncLoadScene(const char *scene_name)
{
    isReadyMutex.lock();
    // TODO: scene loading
    tmpLoaded.reset(scene_allocators_map[scene_name]());
    // using namespace std::chrono_literals;
    // std::this_thread::sleep_for(1000ms);
    // sleep(10000);
    isReady = true;
    isReadyMutex.unlock();
}

void DFSceneManager::SwitchScene(const char *scene_name)
{
    spdlog::debug("Scene switch event. New scene: \"{}\".", scene_name);
    isReady = false;
    std::thread scene_loading_thread(&DFSceneManager::asyncLoadScene, this, scene_name);
    scene_loading_thread.detach();
    handleScene = std::bind(&DFSceneManager::handleLoadingScene, this, std::placeholders::_1);
}

void DFSceneManager::handleLoadingScene(DFScUpdParams_t &render_data)
{
    loadingScreenScene->onHandleFrame(render_data.render_system);
    if (isReadyMutex.try_lock())
    {
        if (isReady)
        {
            spdlog::debug("New scene is ready. Switching...");
            handleScene = std::bind(&DFSceneManager::handleFirstFrameAfterLoad, this, std::placeholders::_1);
        }
        isReadyMutex.unlock();
    }
}

void DFSceneManager::handleFirstFrameAfterLoad(DFScUpdParams_t &render_data)
{
    spdlog::debug("Rendering all textures of a new scene");
    loadingScreenScene->onHandleFrame(render_data.render_system);

    activeScene = std::move(tmpLoaded);

    activeScene->onRenderTextures(render_data.render_system);
    activeScene->onSceneStart(render_data.render_system);

    handleScene = std::bind(&DFSceneManager::handleGameScene, this, std::placeholders::_1);
}

void DFSceneManager::handleGameScene(DFScUpdParams_t &render_data)
{
    activeScene->onHandleFrame(render_data.render_system);
}