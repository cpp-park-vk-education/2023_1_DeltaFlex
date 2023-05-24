#include "../../include/game_ui/GameStaminaBar.hpp"
#include "../../include/ai/StickmanStatsComponent.hpp"
#include <DFEntity.hpp>

int GameStaminaBar::m_margin;
int GameStaminaBar::m_thickness;

static int Map(int value, int min_from, int max_from, int min_to, int max_to)
{
    return min_to + (value - min_from) * (float)(max_to - min_to) / (float)(max_from - min_from);
}

void GameStaminaBar::onInit(DFEntity &gameObject)
{
    m_game_object_pos = &gameObject.transform.position;
    m_thickness = 5;
    m_margin = m_thickness + 3;
}

void GameStaminaBar::onRenderTextures(DFRenderSystem &render_system)
{
    icon = render_system.CreateTextureFromFile("./resources/images/stamina-icon.png");
    icon.width *= 2;
    icon.height *= 2;
}

void GameStaminaBar::Start()
{
    current_health = DFEntity::Find("stickman_0")->getComponent<StickmanStats>()->getHP();
}

void GameStaminaBar::Update()
{
}

void GameStaminaBar::Draw(DFRenderSystem &render_system)
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

    render_system.SetColor(0, 0, 255);
    SDL_Rect health_pos =
    {
        .x = outline_pos.x + m_margin,
        .y = outline_pos.y + m_margin,
        .w = hp_mapped - outline_pos.x,
        .h = outline_pos.h - 2 * m_margin
    };

    render_system.RenderRectFilledUI(health_pos);

    int dx = right_icon_place ? halign_x + 10: - halign_x - 10 - icon.width;

    render_system.RenderTextureUI(icon,
        {
            m_game_object_pos->x + dx,
            m_game_object_pos->y - halign_y + 5
        });
}
