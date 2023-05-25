#include "MainMenuButton.hpp"

void MainMenuButton::onInit(DFEntity &gameObject)
{
    m_gameObjPos = &gameObject.transform.position;
}

void MainMenuButton::onRenderTextures(DFRenderSystem &render_system)
{
    // m_tex = IMG_LoadTexture(render_data.renderer.get(), img_path.c_str());
    m_tex = render_system.CreateTextureFromFile(img_path);
}

void MainMenuButton::Start()
{
    is_active = false;
}

void MainMenuButton::Update()
{
    CheckMouseBounds();
    if (is_active && Input::GetMouseButtonDown(MouseCode::MOUSE_LEFT))
    {
        onClick();
    }
}

void MainMenuButton::Draw(DFRenderSystem &render_system)
{
    SDL_Rect pos =
    {
        .x = (int)(m_gameObjPos->x - halign.x + 10 * is_active),
        .y = (int)(m_gameObjPos->y - halign.y + 10 * is_active),
        .w = (int)halign.x * 2,
        .h = (int)halign.y * 2
    };
    // if(is_active)
    // {
    //     render_system.SetOrigin({-100, -100});
    // }
    // SDL_RenderCopy(render_data.renderer.get(), m_tex, NULL, &pos);
    render_system.RenderTexture(m_tex, NULL, &pos);
}

void MainMenuButton::CheckMouseBounds()
{
    Vector2<float> mouse_pos(Input::GetMouseX(), Input::GetMouseY());
    is_active = (*m_gameObjPos - halign < mouse_pos && mouse_pos < *m_gameObjPos + halign);
}