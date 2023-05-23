#include "MainMenuSlider.hpp"

template <typename T>
static T Map(T value, T min_from, T max_from, T min_to, T max_to)
{
    return min_to + (value - min_from) * ((float)(max_to - min_to) / (float)(max_from - min_from));
}


void MainMenuSlider::onInit(DFEntity &gameObject)
{
    m_gameObjPos = &gameObject.transform.position;
    m_pos = 0;
    m_mouse_pos = {0, 0};
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

    if (Input::GetMouseButtonDown(MouseCode::MOUSE_LEFT))
    {
        is_dragged = true;
        onMouseDrag();
    }
    
    if (Input::GetMouseButtonUp(MouseCode::MOUSE_LEFT))
    {
        is_dragged = false;
    }
}

void MainMenuSlider::onMouseDrag()
{
    m_pos = std::max<int>(halign_line.x, Input::GetMouseX());
}

int MainMenuSlider::getValue() const
{
    return Map<int>(m_pos, s_map_range.first, s_map_range.second, m_start, m_end);
}

void MainMenuSlider::Draw(DFRenderSystem &render_system)
{
    SDL_Rect line_pos =
    {
        .x = (int)(m_gameObjPos->x - halign_line.x),
        .y = (int)(m_gameObjPos->y - halign_line.y),
        .w = (int)halign_line.x * 2,
        .h = (int)halign_line.y * 2
    };
    render_system.RenderTexture(m_tex_slider, NULL, &line_pos);

    SDL_Rect slider_pos =
    {
        .x = (int)(m_gameObjPos->x - halign_slider.x + m_pos),
        .y = (int)(m_gameObjPos->y - halign_slider.y),
        .w = (int)halign_slider.x * 2,
        .h = (int)halign_slider.y * 2
    };
    render_system.RenderTexture(m_tex_slider, NULL, &slider_pos);
}

void MainMenuSlider::CheckMouseBounds()
{
    Vector2<float> mouse_pos(Input::GetMouseX(), Input::GetMouseY());
    is_active = (*m_gameObjPos - halign_slider < mouse_pos && mouse_pos < *m_gameObjPos + halign_slider);
}

// bool MainMenuSlider::GetMouseMoved()
// {
//     Vector2<float> new_pos(Input::GetMouseX(), Input::GetMouseY());
//     std::cout << new_pos;
//     if (new_pos != m_mouse_pos)
//     {
//         m_mouse_pos = new_pos;
//         return true;
//     }
//     return false;
// }
