#include "../../include/game_ui/GameHealthBar.hpp"
#include "../../include/ai/StickmanStatsComponent.hpp"
#include <DFEntity.hpp>

int GameHealthBar::m_margin;
int GameHealthBar::m_thickness;

static int Map(int value, int min_from, int max_from, int min_to, int max_to)
{
    return min_to + (value - min_from) * (float)(max_to - min_to) / (float)(max_from - min_from);
}

void GameHealthBar::onInit(DFEntity &gameObject)
{
    m_game_object_pos = &gameObject.transform.position;
    m_thickness = 5;
    m_margin = m_thickness + 3;
}

void GameHealthBar::onRenderTextures(DFRenderSystem &render_system)
{

}

void GameHealthBar::Start()
{
    current_health = DFEntity::Find("stickman_0")->getComponent<StickmanStats>()->getHP();
}

void GameHealthBar::Update()
{

}

void GameHealthBar::Draw(DFRenderSystem &render_system)
{
    int halign_x = (int)halign.x, halign_y = (int)halign.y;
    SDL_Rect outline_pos =
    {
        .x = (int)(m_game_object_pos->x - halign_x),
        .y = (int)(m_game_object_pos->y - halign_y),
        .w = halign_x * 2,
        .h = halign_y * 2
    };

    render_system.SetColor(255, 255, 255);
    render_system.RenderRectHollowUI(outline_pos, m_thickness);

    int hp_mapped = Map(
        *current_health,
        0, 100,
        outline_pos.x,
        outline_pos.x + outline_pos.w - 2 * m_margin
    );

    render_system.SetColor(255, 0, 0);
    SDL_Rect health_pos =
    {
        .x = outline_pos.x + m_margin,
        .y = outline_pos.y + m_margin,
        .w = hp_mapped - outline_pos.x,
        .h = outline_pos.h - 2 * m_margin
    };

    render_system.RenderRectFilledUI(health_pos);
}
