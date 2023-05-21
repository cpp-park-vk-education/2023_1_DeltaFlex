#include <DFLoadingScene.hpp>

DFLoadingScene::DFLoadingScene()
{
    // surf = IMG_Load("./loading.png");
    src.x = 0;
    src.y = 0;
    src.w = 1280;
    src.h = 720;

    dst.x = 0;
    dst.y = 0;
    dst.w = 1280;
    dst.h = 720;
}

void DFLoadingScene::onRenderTextures(DFRenderSystem &render_system)
{
    // texture = SDL_CreateTextureFromSurface(render_data.renderer.get(), surf);
}

void DFLoadingScene::onSceneStart(DFRenderSystem &render_system)
{}

void DFLoadingScene::onHandleFrame(DFRenderSystem &render_system)
{
    // SDL_RenderCopy(render_data.renderer.get(), texture, &src, &dst);
    // SDL_RenderCopy(render_data.renderer.get(), texture, NULL, &dst);
}