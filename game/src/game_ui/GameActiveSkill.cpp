#include "../../include/game_ui/GameActiveSkill.hpp"
#include "../../include/ai/StickmanStatsComponent.hpp"
#include <DFEntity.hpp>

void GameActiveSkill::onInit(DFEntity &gameObject)
{
    m_game_object_pos = &gameObject.transform.position;
}

void GameActiveSkill::onRenderTextures(DFRenderSystem &render_system)
{
    // icon = render_system.CreateTextureFromFile("./resources/images/hp-icon.png");
    // icon.width *= 4;
    // icon.height *= 4;
}

void GameActiveSkill::Start()
{
    // current_health = DFEntity::Find("stickman_0")->getComponent<StickmanStats>()->getHP();
}

void GameActiveSkill::Update()
{

}

void GameActiveSkill::Draw(DFRenderSystem &render_system)
{
    int neuron_radius = 25;
    int neuron_distance = 10;
    int neuron_dx = 2 * neuron_radius + neuron_distance;

    struct Neuron_t
    {
        int x;
        int y;
        int r;
        int g;
        int b;
        int op; // opacity
    };

    struct Line_t
    {
        int x0;
        int y0;
        int x1;
        int y1;
    };

    std::vector<Neuron_t> neurons(6, {0, 0, 0, 0, 0, 255});

    neurons[0] = {static_cast<int>(m_game_object_pos->x + neuron_radius),
                    static_cast<int>(m_game_object_pos->y + neuron_radius), 0, 0, 0, 255};

    neurons[1] = {static_cast<int>(m_game_object_pos->x + neuron_radius), 
                    static_cast<int>(m_game_object_pos->y + neuron_radius + neuron_dx), 0, 0, 0, 255};

    neurons[2] = {static_cast<int>(m_game_object_pos->x + neuron_radius), 
                    static_cast<int>(m_game_object_pos->y + neuron_radius + 2 * neuron_dx), 0, 0, 0, 255};

    neurons[3] = {static_cast<int>(m_game_object_pos->x + neuron_radius + neuron_dx), 
                    static_cast<int>(m_game_object_pos->y + neuron_radius + neuron_dx / 2), 0, 0, 0, 255};

    neurons[4] = {static_cast<int>(m_game_object_pos->x + neuron_radius + neuron_dx), 
                    static_cast<int>(m_game_object_pos->y + neuron_radius + neuron_dx / 2 * 3), 0, 0, 0, 255};

    neurons[5] = {static_cast<int>(m_game_object_pos->x + neuron_radius + 2 * neuron_dx), 
                    static_cast<int>(m_game_object_pos->y + neuron_radius + neuron_dx), 0, 0, 0, 255};
    
    std::vector<Line_t> lines(8);

    lines[0] = {neurons[0].x, neurons[0].y, neurons[3].x, neurons[3].y};
    lines[1] = {neurons[0].x, neurons[0].y, neurons[4].x, neurons[4].y};
    lines[2] = {neurons[1].x, neurons[1].y, neurons[3].x, neurons[3].y};
    lines[3] = {neurons[1].x, neurons[1].y, neurons[4].x, neurons[4].y};
    lines[4] = {neurons[2].x, neurons[2].y, neurons[3].x, neurons[3].y};
    lines[5] = {neurons[2].x, neurons[2].y, neurons[4].x, neurons[4].y};
    lines[6] = {neurons[3].x, neurons[3].y, neurons[5].x, neurons[5].y};
    lines[7] = {neurons[4].x, neurons[4].y, neurons[5].x, neurons[5].y};

    for (const auto &line: lines)
        thickLineRGBA(render_system.getRenderer(), line.x0, line.y0, line.x1, line.y1, 2, 0, 0, 0, 255);

    for (const auto &neuron: neurons)
        filledCircleRGBA(render_system.getRenderer(), neuron.x, neuron.y, neuron_radius, neuron.r, neuron.g, neuron.b, neuron.op);
    
    if (is_up_skill)
    {
        DFTexture icon = render_system.CreateTextureFromFile("./resources/images/sword-icon.png");
        icon.width = neuron_radius;
        icon.height = neuron_radius;

        render_system.RenderTextureUI(
            icon,
            {
                static_cast<float>(neurons[5].x - neuron_radius / 2),
                static_cast<float>(neurons[5].y - neuron_radius / 2)
            });
    }
    else
    {
        DFTexture icon = render_system.CreateTextureFromFile("./resources/images/hp-icon.png");
        icon.width = neuron_radius;
        icon.height = neuron_radius;

        render_system.RenderTextureUI(
            icon,
            {
                static_cast<float>(neurons[5].x - neuron_radius / 2),
                static_cast<float>(neurons[5].y - neuron_radius / 2)
            });
    }

    // int halign_x = (int)halign.x, halign_y = (int)halign.y;
    // SDL_Rect outline_pos =
    // {
    //     .x = (int)(m_game_object_pos->x - halign_x),
    //     .y = (int)(m_game_object_pos->y - halign_y),
    //     .w = halign_x * 2,
    //     .h = halign_y * 2
    // };

    // render_system.SetColor(255, 255, 255);
    // render_system.RenderRectHollowUI(outline_pos, m_thickness);

    // int hp_mapped = Map(
    //     *current_health,
    //     0, 100,
    //     outline_pos.x,
    //     outline_pos.x + outline_pos.w - 2 * m_margin
    // );

    // render_system.SetColor(255, 0, 0);
    // SDL_Rect health_pos =
    // {
    //     .x = outline_pos.x + m_margin,
    //     .y = outline_pos.y + m_margin,
    //     .w = hp_mapped - outline_pos.x,
    //     .h = outline_pos.h - 2 * m_margin
    // };

    // render_system.RenderRectFilledUI(health_pos);

    // int dx = right_icon_place ? halign_x + 10: - halign_x - 10 - icon.width;

    // render_system.RenderTextureUI(icon,
    //     {
    //         m_game_object_pos->x + dx,
    //         m_game_object_pos->y - halign_y
    //     });
}
