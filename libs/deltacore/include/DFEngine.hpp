#pragma once

#include <memory>
#include <DFSceneManager.hpp>
#include <DFAudioManager.hpp>
#include <DFVideoParams.hpp>

class DFEngine
{
private:
    std::unique_ptr<DFSceneManager> sceneManager;
    std::unique_ptr<DFAudioManager> audioManager;
    DFScUpdParams_t render_data;
    DFVideoParams_t video_params;

    int targetFrameRate;
    bool gameIsActive;

    void HandleEvents(void);

public:
    static DFEngine *Instance;
    static double deltaTime;
    static int currentFrameRate;

    DFEngine();

    void EngineInit();
    void EngineCycle();

    void SwitchScene(const char *scene_name);
    void AppendSceneAllocator(std::string key, scene_allocator_t allocator) { sceneManager->AppendSceneAllocator(key, allocator); };
    static DFScene *GetActiveScene(void) { return Instance->sceneManager->activeScene.get(); };
    static Uint64 GetTime() { return SDL_GetTicks64(); }
    static Vector2<int> GetWindowLogicalSize() { return { Instance->video_params.logicalWidth, Instance->video_params.logicalHeight }; }

    static void setWindowTitle(std::string title) { SDL_SetWindowTitle(Instance->render_data.window.get(), title.c_str()); }
    static void exitGame() { Instance->gameIsActive = false; }
};
