#include "MainMenuCheckBox.hpp"

void MainMenuCheckBox::onInit(DFEntity &gameObject)
{
    m_gameObjPos = &gameObject.transform.position;
    m_checked = true;
}

void MainMenuCheckBox::onRenderTextures(DFRenderSystem &render_system)
{
    m_tex_checked = render_system.CreateTextureFromFile(img_path_checked);
    m_tex_unchecked = render_system.CreateTextureFromFile(imp_path_unchecked);
    m_tex_active = m_checked ? m_tex_checked : m_tex_unchecked;

    std::cout << (void *)m_tex_checked << "  " << (void *)m_tex_unchecked << "\n";
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
    m_tex_active = m_checked ? m_tex_checked : m_tex_unchecked;
}

bool MainMenuCheckBox::isChecked() const
{
    return m_checked;
}

void MainMenuCheckBox::Draw(DFRenderSystem &render_system)
{
    SDL_Rect pos =
    {
        .x = (int)(m_gameObjPos->x - halign.x + 10 * is_active),
        .y = (int)(m_gameObjPos->y - halign.y + 10 * is_active),
        .w = (int)halign.x * 2,
        .h = (int)halign.y * 2
    };
    render_system.RenderTexture(m_tex_active, NULL, &pos);
}

void MainMenuCheckBox::CheckMouseBounds()
{
    Vector2<float> mouse_pos(Input::GetMouseX(), Input::GetMouseY());
    is_active = (*m_gameObjPos - halign < mouse_pos && mouse_pos < *m_gameObjPos + halign);
}
