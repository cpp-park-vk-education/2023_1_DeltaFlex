#include "UiButton.hpp"

void UiButton::onInit(DFEntity &gameObject)
{
    m_gameObjPos = &gameObject.transform.position;
}

void UiButton::onRenderTextures(DFRenderSystem &render_system)
{
    // m_tex = IMG_LoadTexture(render_data.renderer.get(), img_path.c_str());
    m_tex = render_system.CreateTextureFromFile(img_path);
}

void UiButton::Start()
{
    is_active = false;
}

void UiButton::Update()
{
    CheckMouseBounds();
    if (is_active && Input::GetMouseButtonDown(MouseCode::MOUSE_LEFT))
    {
        onClick();
    }
}

void UiButton::Draw(DFRenderSystem &render_system)
{
    Vector2<float> pos =
    {
        (m_gameObjPos->x - halign.x + shift.x + 10 * is_active),
        (m_gameObjPos->y - halign.y + shift.y + 10 * is_active),
    };
    // if(is_active)
    // {
    //     render_system.SetOrigin({-100, -100});
    // }
    // SDL_RenderCopy(render_data.renderer.get(), m_tex, NULL, &pos);
    render_system.RenderTextureUI(m_tex, pos);
}

void UiButton::CheckMouseBounds()
{
    Vector2<float> mouse_pos(Input::GetMouseX(), Input::GetMouseY());
    is_active = (*m_gameObjPos - halign + shift < mouse_pos && mouse_pos < *m_gameObjPos + halign + shift);
}
