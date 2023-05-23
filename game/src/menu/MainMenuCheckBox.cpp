#include "MainMenuCheckBox.hpp"

void MainMenuCheckBox::onInit(DFEntity &gameObject)
{
    m_gameObjPos = &gameObject.transform.position;
    m_checked = true;
}

void MainMenuCheckBox::onRenderTextures(DFRenderSystem &render_system)
{
    m_tex_body = render_system.CreateTextureFromFile(img_path_body);
    m_tex_tick = render_system.CreateTextureFromFile(img_path_tick);
}

void MainMenuCheckBox::Start()
{
    is_active = false;
}

void MainMenuCheckBox::Update()
{
    CheckMouseBounds();
    if (is_active && Input::GetMouseButtonDown(MouseCode::MOUSE_LEFT))
    {
        onClick();
    }
}

void MainMenuCheckBox::onClick()
{
    m_checked = !m_checked;
}

bool MainMenuCheckBox::isChecked() const
{
    return m_checked;
}

void MainMenuCheckBox::Draw(DFRenderSystem &render_system)
{
    if (m_checked)
    {
        SDL_Rect pos =
        {
            .x = (int)(m_gameObjPos->x - halign.x),
            .y = (int)(m_gameObjPos->y - halign.y - 10),
            .w = (int)halign.x * 2,
            .h = (int)halign.y * 2
        };
        render_system.RenderTexture(m_tex_tick, NULL, &pos);
    }

    SDL_Rect pos =
    {
        .x = (int)(m_gameObjPos->x - halign.x),
        .y = (int)(m_gameObjPos->y - halign.y),
        .w = (int)halign.x * 2,
        .h = (int)halign.y * 2
    };
    render_system.RenderTexture(m_tex_body, NULL, &pos);
}

void MainMenuCheckBox::CheckMouseBounds()
{
    Vector2<float> mouse_pos(Input::GetMouseX(), Input::GetMouseY());
    is_active = (*m_gameObjPos - halign < mouse_pos && mouse_pos < *m_gameObjPos + halign);
}
