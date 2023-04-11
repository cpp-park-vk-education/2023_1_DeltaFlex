#pragma once

#include <mutex>
#include <functional>
#include <memory>
#include <unordered_map>

#include <DFScene.hpp>

class DFSceneManager
{
private:
    std::unique_ptr<DFScene> activeScene;
    std::unique_ptr<DFScene> loadingScreenScene;
    std::unique_ptr<DFScene> tmpLoaded;

    std::unordered_map<std::string, scene_allocator_t> scene_allocators_map;
    bool isReady;
    std::mutex isReadyMutex; 

    void handleLoadingScene(DFScUpdParams_t &render_data);
    void handleFirstFrameAfterLoad(DFScUpdParams_t &render_data);
    void handleGameScene(DFScUpdParams_t &render_data);

    void asyncLoadScene(const char *scene_name);
public:
    DFSceneManager();
    void AppendSceneAllocator(std::string key, scene_allocator_t allocator);
    void initSceneManager(DFScUpdParams_t &render_data, const char *entrypoint);
    std::function<void(DFScUpdParams_t &)> handleScene;

    void SwitchScene(const char *scene_name);

    friend class DFEngine;
};