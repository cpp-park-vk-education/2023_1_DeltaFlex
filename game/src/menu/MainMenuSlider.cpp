#include "MainMenuSlider.hpp"

template <typename T>
static T Map(T value, T min_from, T max_from, T min_to, T max_to)
{
    return min_to + (value - min_from) * ((float)(max_to - min_to) / (float)(max_from - min_from));
}


void MainMenuSlider::onInit(DFEntity &gameObject)
{
    m_gameObjPos = &gameObject.transform.position;

    m_start_pix = m_gameObjPos->x - halign_line.x;
    m_end_pix = m_gameObjPos->x + halign_line.x;

    m_pos_pix = m_start_pix;
}

void MainMenuSlider::onRenderTextures(DFRenderSystem &render_system)
{
    m_tex_line = render_system.CreateTextureFromFile(img_path_line);
    m_tex_slider = render_system.CreateTextureFromFile(img_path_slider);
}

void MainMenuSlider::Start()
{
    is_active = false;
    is_dragged = false;
}

void MainMenuSlider::Update()
{
    if (is_dragged)
    {
        onMouseDrag();
    }
    else
    {
        CheckMouseBounds();
    }

    if (is_active && Input::GetMouseButtonDown(MouseCode::MOUSE_LEFT))
    {
        is_dragged = true;
        onMouseDrag();
    }
    
    if (is_dragged && Input::GetMouseButtonUp(MouseCode::MOUSE_LEFT))
    {
        is_dragged = false;
    }
}

void MainMenuSlider::onMouseDrag()
{
    m_pos_pix = std::max<int>(std::min<int>(m_end_pix, Input::GetMouseX()), m_start_pix);
}

int MainMenuSlider::getValue() const
{
    return Map<int>(m_pos_pix, m_start_pix, m_end_pix, m_start, m_end);
}

void MainMenuSlider::Draw(DFRenderSystem &render_system)
{
    SDL_Rect line_pos =
    {
        .x = (int)(m_start_pix),
        .y = (int)(m_gameObjPos->y - halign_line.y),
        .w = (int)halign_line.x * 2,
        .h = (int)halign_line.y * 2
    };
    render_system.RenderTexture(m_tex_line, NULL, &line_pos);

    SDL_Rect slider_pos =
    {
        .x = (int)(m_pos_pix - halign_slider.x),
        .y = (int)(line_pos.y - halign_slider.y),
        .w = (int)halign_slider.x * 2,
        .h = (int)halign_slider.y * 2
    };
    render_system.RenderTexture(m_tex_slider, NULL, &slider_pos);
}

void MainMenuSlider::CheckMouseBounds()
{
    Vector2<float> mouse_pos(Input::GetMouseX(), Input::GetMouseY());
    Vector2<float> bounding_box{halign_line.x, halign_slider.y};
    is_active = (*m_gameObjPos - bounding_box < mouse_pos && mouse_pos < *m_gameObjPos + bounding_box);
}
