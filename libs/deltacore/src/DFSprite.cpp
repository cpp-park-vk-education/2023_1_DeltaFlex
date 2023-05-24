#include <DFSprite.hpp>

DFSprite::DFSprite(const char *resoursePath, DFTransform &tt, int _x_offset, int _y_offset):
    target_transform(tt),
    x_offset(_x_offset),
    y_offset(_y_offset)
{
    surface = IMG_Load(resoursePath);
    // texture = NULL;
    sprite_rect.w = surface->w;
    sprite_rect.h = surface->h;
}

DFSprite::DFSprite(const char *resoursePath, DFTransform &tt):
    target_transform(tt)
{
    surface = IMG_Load(resoursePath);
    // texture = NULL;
    sprite_rect.w = surface->w;
    sprite_rect.h = surface->h;

    x_offset = -sprite_rect.w / 2;
    y_offset = -sprite_rect.h / 2;
}


DFSprite::~DFSprite()
{
    // SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void DFSprite::onRenderTextures(DFRenderSystem &render_system)
{
    // texture = SDL_CreateTextureFromSurface(render_data.renderer.get(), surface);
    texture = render_system.CreateTextureFromSurface(surface);
}

void DFSprite::Draw(DFRenderSystem &render_system)
{
    sprite_rect.x = target_transform.position.x + x_offset;
    sprite_rect.y = target_transform.position.y + y_offset;

    // SDL_RenderCopy(render_data.renderer.get(), texture, NULL, &sprite_rect);
    render_system.RenderTexture(texture, NULL, &sprite_rect);
}