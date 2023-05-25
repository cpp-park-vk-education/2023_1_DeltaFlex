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
    m_tex_one = render_system.CreateTextureFromFile("./resources/images/sword-icon.png");
    m_tex_two = render_system.CreateTextureFromFile("./resources/images/hp-icon.png");
    render_system.SetColor(255, 255, 255);
    neuron_textures[0] = render_system.CreateHollowCircleTex(20, 5);
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
    int neuron_radius = 20;
    int neuron_distance = 10;
    int neuron_dx = 2 * neuron_radius + neuron_distance;

    struct Neuron_t
    {
        int x;
        int y;
        int r = 255;
        int g = 255;
        int b = 255;
        int op = 255; // opacity
    };

    struct Line_t
    {
        int x0;
        int y0;
        int x1;
        int y1;
    };

    std::vector<Neuron_t> neurons(6);

    neurons[0] = {static_cast<int>(m_game_object_pos->x + neuron_radius),
                  static_cast<int>(m_game_object_pos->y + neuron_radius)};

    neurons[1] = {static_cast<int>(m_game_object_pos->x + neuron_radius),
                  static_cast<int>(m_game_object_pos->y + neuron_radius + neuron_dx)};

    neurons[2] = {static_cast<int>(m_game_object_pos->x + neuron_radius),
                  static_cast<int>(m_game_object_pos->y + neuron_radius + 2 * neuron_dx)};

    neurons[3] = {static_cast<int>(m_game_object_pos->x + neuron_radius + neuron_dx),
                  static_cast<int>(m_game_object_pos->y + neuron_radius + neuron_dx / 2)};

    neurons[4] = {static_cast<int>(m_game_object_pos->x + neuron_radius + neuron_dx),
                  static_cast<int>(m_game_object_pos->y + neuron_radius + neuron_dx / 2 * 3)};

    neurons[5] = {static_cast<int>(m_game_object_pos->x + neuron_radius + 2 * neuron_dx),
                  static_cast<int>(m_game_object_pos->y + neuron_radius + neuron_dx)};

    std::vector<Line_t> lines(8);

    lines[0] = {neurons[0].x, neurons[0].y, neurons[3].x, neurons[3].y};
    lines[1] = {neurons[0].x, neurons[0].y, neurons[4].x, neurons[4].y};
    lines[2] = {neurons[1].x, neurons[1].y, neurons[3].x, neurons[3].y};
    lines[3] = {neurons[1].x, neurons[1].y, neurons[4].x, neurons[4].y};
    lines[4] = {neurons[2].x, neurons[2].y, neurons[3].x, neurons[3].y};
    lines[5] = {neurons[2].x, neurons[2].y, neurons[4].x, neurons[4].y};
    lines[6] = {neurons[3].x, neurons[3].y, neurons[5].x, neurons[5].y};
    lines[7] = {neurons[4].x, neurons[4].y, neurons[5].x, neurons[5].y};

    for (const auto &line : lines)
        thickLineRGBA(render_system.getRenderer(), line.x0, line.y0, line.x1, line.y1, 2, 255, 255, 255, 255);

    for (const auto &neuron : neurons)
    {
        render_system.SetColor(neuron.r, neuron.g, neuron.b, neuron.op);
        // render_system.RenderHollowCircleUI({(float)neuron.x, (float)neuron.y}, neuron_radius, 3);
        render_system.RenderTextureUI(neuron_textures[0], {(float)neuron.x - neuron_radius, (float)neuron.y- neuron_radius});

        // render_system.SetColor(255, 0, 0, 255);
        // render_system.RenderFilledCircle();
    }

    if (is_up_skill)
    {
        // DFTexture icon = render_system.CreateTextureFromFile("./resources/images/sword-icon.png");
        m_tex_one.width = neuron_radius;
        m_tex_one.height = neuron_radius;

        render_system.RenderTextureUI(
            m_tex_one,
            {static_cast<float>(neurons[5].x - neuron_radius / 2),
             static_cast<float>(neurons[5].y - neuron_radius / 2)});
    }
    else
    {
        // DFTexture icon = render_system.CreateTextureFromFile("./resources/images/hp-icon.png");
        m_tex_two.width = neuron_radius;
        m_tex_two.height = neuron_radius;

        render_system.RenderTextureUI(
            m_tex_two,
            {static_cast<float>(neurons[5].x - neuron_radius / 2),
             static_cast<float>(neurons[5].y - neuron_radius / 2)});
    }
}
