#include <DFEngine.hpp>
#include <DFInputSystem.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <sys/time.h>

#include <spdlog/spdlog.h>
#include <DFIniParser.hpp>


static inline unsigned long long microseconds_now()
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
    {
        return (unsigned long long) - 1;
    }
    return val.tv_sec * 1000000ULL + val.tv_usec;
}

DFEngine *DFEngine::Instance(nullptr);
double DFEngine::deltaTime = 1;
int DFEngine::currentFrameRate = 60;

DFEngine::DFEngine()
#ifdef EXPERIMENTAL_ALLOCATOR
    :df_allocator(1024 * 1024 * 10)
#endif
{
    if (Instance != nullptr)
    {
        spdlog::throw_spdlog_ex("Only 1 instane of engine is allowed");
    }
    sceneManager = std::make_unique<DFSceneManager>();
    audioManager = std::make_unique<DFAudioManager>();
    Mix_VolumeMusic(16);
    Instance = this;
    spdlog::debug("Engine instance created successfuly");
}

void static initVideoParams(DFVideoParams_t &video_params, DFIni::IniFile &settings)
{
    video_params.logicalWidth = 1280;
    video_params.logicalHeight = 720;
    video_params.realWidth = settings["window"]["width"].as<int>();
    video_params.realHeight = settings["window"]["height"].as<int>();
    if (video_params.realWidth * video_params.realHeight == 0)
    {
        spdlog::critical("Incorrect settings.ini");
        spdlog::throw_spdlog_ex("Incorrect settings.ini");
    }
}

void DFEngine::EngineInit(void)
{
    spdlog::info("Initialising engine...");
    DFIni::IniFile settings;
    try
    {
        settings.load("./settings.ini");
    }
    catch (const std::exception &e)
    {
        spdlog::critical("Unable to open settings.ini");
        spdlog::throw_spdlog_ex("Unable to open settings.ini");
    }
    spdlog::debug("Reading settings from: {}...", "settings.ini");
    initVideoParams(video_params, settings);
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        spdlog::critical("SDL could not initialize!");
        spdlog::throw_spdlog_ex(SDL_GetError());
    }
    spdlog::info("SDL initialized successfuly");

    render_data.window.reset(SDL_CreateWindow("Mentis Bellum", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, video_params.realWidth, video_params.realHeight, SDL_WINDOW_SHOWN));
    if (render_data.window.get() == NULL)
    {
        spdlog::critical("Window could not be created!");
        spdlog::throw_spdlog_ex(SDL_GetError());
    }
    spdlog::info("Window created successfuly");
    if (settings["window"]["compositing"].as<bool>())
    {
        spdlog::info("[settings] Enabling compositing");
        SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
    }
    int renderer_flags = 0;
    if (settings["window"]["vsync"].as<bool>())
    {
        spdlog::info("[settings] Enabling vsync");
        renderer_flags |= SDL_RENDERER_PRESENTVSYNC;
    }
    if (settings["window"]["hardware_acceleration"].as<bool>())
    {
        spdlog::info("[settings] Enabling hardware_acceleration");
        renderer_flags |= SDL_RENDERER_ACCELERATED;
    }
    spdlog::debug("render_flasgs={}", renderer_flags);
    render_data.render_system.setRenderer(SDL_CreateRenderer(render_data.window.get(), 0, renderer_flags));
    if (render_data.render_system.getRenderer() == NULL)
    {
        spdlog::critical("Renderer could not be created!");
        spdlog::throw_spdlog_ex(SDL_GetError());
    }
    spdlog::info("Renderer created successfuly");
    if (SDL_RenderSetLogicalSize(render_data.render_system.getRenderer(), video_params.logicalWidth, video_params.logicalHeight) != 0)
    {
        spdlog::error(SDL_GetError());
    }
    // activeScene = scene_allocators["default"](ScreenParams, SdlData);
    gameIsActive = true;
    sceneManager->initSceneManager(render_data, "default");
    spdlog::info("Initialise engine successful!");
};

void DFEngine::EngineCycle(void)
{
    spdlog::info("starting main loop...");
    unsigned long long cur_time, was_time = microseconds_now();
    double to_sleep;
    while (gameIsActive)
    {
        cur_time = microseconds_now();
        deltaTime = ((double)(cur_time - was_time)) / 1000000.;
        currentFrameRate = (deltaTime != 0) ? (int)(1 / deltaTime) : INFINITY;
        // char tmp[10] = { 0 };
        // SDL_SetWindowTitle(render_data.window.get(), SDL_itoa((int)currentFrameRate, tmp, 10));

        DFInputSystem::InputSystemOnFrameStart();
        HandleEvents();

        // SDL_RenderClear(render_data.renderer.get());
        render_data.render_system.Clear();
        sceneManager->handleScene(render_data);
        render_data.render_system.Present();
        // SDL_RenderPresent(render_data.renderer.get());
        Input::InputSystemOnFrameEnd();

        was_time = cur_time;
        to_sleep = 1000. / targetFrameRate - ((double)(microseconds_now() - was_time)) / 1000.;
        SDL_Delay((to_sleep > 0) ? to_sleep : 0);
    }
    spdlog::info("exiting main loop...");
}

void DFEngine::SwitchScene(const char *scene_name)
{
    sceneManager->SwitchScene(scene_name);
}

void DFEngine::HandleEvents(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                DFInputSystem::InputSystemOnKeyboardEvent(event.key);
                break;

            case SDL_MOUSEBUTTONDOWN:
                DFInputSystem::InputSystemOnMouseDown(event.button);
                break;

            case SDL_MOUSEBUTTONUP:
                DFInputSystem::InputSystemOnMouseUp(event.button);
                break;

            case SDL_QUIT:
                gameIsActive = false;
                break;

            default:
                break;
        }
    }
}