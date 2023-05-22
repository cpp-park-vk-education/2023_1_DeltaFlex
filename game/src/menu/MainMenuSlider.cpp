#include "MainMenuSlider.hpp"

void MainMenuSlider::onInit(DFEntity &gameObject)
{
    m_gameObjPos = &gameObject.transform.position;
    m_checked = true;
}

void MainMenuSlider::onRenderTextures(DFRenderSystem &render_system)
{
    m_tex_slider = render_system.CreateTextureFromFile(img_path_slider);
}

void MainMenuSlider::Start()
{
    is_active = false;
}

void MainMenuSlider::Update()
{
    CheckMouseBounds();
    if (is_active && Input::GetMouseButtonDown(MouseCode::MOUSE_LEFT))
    {
        onClick();
    }
}

void MainMenuSlider::onClick()
{
    CheckMouseBounds();
    if (is_active)
    {
    }
}

int MainMenuSlider::getValue() const
{
    return m_current;
}

void MainMenuSlider::Draw(DFRenderSystem &render_system)
{
    SDL_Rect pos =
    {
        .x = (int)(m_gameObjPos->x - halign.x + 10 * is_active),
        .y = (int)(m_gameObjPos->y - halign.y + 10 * is_active),
        .w = (int)halign.x * 2,
        .h = (int)halign.y * 2
    };
    render_system.RenderTexture(m_tex_slider, NULL, &pos);
}

void MainMenuSlider::CheckMouseBounds()
{
    Vector2<float> mouse_pos(Input::GetMouseX(), Input::GetMouseY());
    is_active = (*m_gameObjPos - halign < mouse_pos && mouse_pos < *m_gameObjPos + halign);
}

void MainMenuSlider::Map(int value, int min1, int max1, int min2, int max2)
{
}
