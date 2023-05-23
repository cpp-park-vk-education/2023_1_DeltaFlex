#include "ControlComponents.hpp"
#include <DFInputSystem.hpp>
#include <DFWorldScene.hpp>

void StickmanRestarter::onInit(DFEntity &gameObject)
{
    my_stickman = gameObject.getComponent<StickmanPhysicsComponent>();
}

void StickmanRestarter::RestartStickman()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-400, 400);

    Vector2<float> align(dist(gen), 475.873 - 70);
    my_stickman->m_pointMasses[0]->m_pos = align + Vector2<float>(619.665, 23.703);
    my_stickman->m_pointMasses[1]->m_pos = align + Vector2<float>(540.665, 153.6235);
    my_stickman->m_pointMasses[1]->m_pos = align + Vector2<float>(700.665, 153.6235);
    my_stickman->m_pointMasses[2]->m_pos = align + Vector2<float>(619.659, 137.391);
    my_stickman->m_pointMasses[3]->m_pos = align + Vector2<float>(619.63, 83.7396);
    my_stickman->m_pointMasses[4]->m_pos = align + Vector2<float>(619.669, 83.7609);
    my_stickman->m_pointMasses[5]->m_pos = align + Vector2<float>(619.554, 137.073);
    my_stickman->m_pointMasses[6]->m_pos = align + Vector2<float>(619.664, 137.094);
    my_stickman->m_pointMasses[7]->m_pos = align + Vector2<float>(634.704, 190.655);
    my_stickman->m_pointMasses[8]->m_pos = align + Vector2<float>(604.614, 190.794);
    my_stickman->m_pointMasses[9]->m_pos = align + Vector2<float>(638.774, 313.988);
    my_stickman->m_pointMasses[10]->m_pos = align + Vector2<float>(600.544, 314.127);
    for (auto &x : my_stickman->m_pointMasses)
    {
        x->m_acceleration = { 0, 0 };
        x->m_oldPos = x->m_pos;
    }
    my_stickman->m_pointMasses[2]->pinTo({my_stickman->m_pointMasses[2]->m_pos.x, my_stickman->m_pointMasses[2]->m_pos.y});
    my_stickman->m_pointMasses[9]->pinTo({my_stickman->m_pointMasses[9]->m_pos.x, my_stickman->m_pointMasses[9]->m_pos.y});
    my_stickman->m_pointMasses[10]->pinTo({my_stickman->m_pointMasses[10]->m_pos.x, my_stickman->m_pointMasses[10]->m_pos.y});
}

void StickmanAI::onInit(DFEntity &gameObject)
{
    my_stickman = gameObject.getComponent<StickmanPhysicsComponent>();
    model = new Model(my_stickman);
}

void StickmanAI::Update()
{
    auto result = model->predict();
    my_stickman->MoveAll(result);
    model->updateRecord();
}

bool StickmanAI::getActive()
{
    return model->getActive();
}

void EraComponent::onInit(DFEntity &gameObject)
{
    era = 1;
    time = 0;
    best = 0;
    multi = 1;
    Restart();
}

void EraComponent::Restart()
{
    for (size_t i = 0; i < stickmans.size(); i++)
    {
        stickmans[i]->getComponent<StickmanRestarter>()->RestartStickman();
        stickmans[i]->getComponent<StickmanAI>()->model->resetRecord();
    }
}

std::vector<Model*> EraComponent::GetModels()
{
    std::vector<Model*> models;
    for (size_t i = 0; i < stickmans.size(); i++)
    {
        models.push_back(stickmans[i]->getComponent<StickmanAI>()->model);
    }
    return models;
}

void EraComponent::Update()
{
    auto models = GetModels();
    bool active = false;
    for (auto &model: models)
        if (model->getActive())
        {
            active = true;
            break;
        }
    
    
    if (!active)
        time = 6000;
    
    time++;
    if (time > 6000)
    {
        auto models = GetModels();
        int current = models[0]->getRecord();
        int max_i;
        for (size_t i = 0; i < models.size(); i++)
        {
            max_i = i;
            current = std::max(static_cast<int>(models[i]->getRecord()), current);
        }

        models[max_i]->save(era, current);

        if (current > best || (current / static_cast<float>(best) > 0.4))
        {
            Evolution evo(models);
            evo.Selection_Tournament(2, 5);
            evo.Crossing();
            evo.Mutation(10, 60);
        }
        if (current > best)
            best = current;

        std::cout << current << std::endl;

        DFEngine::setWindowTitle(std::to_string(era) +
        " " + std::to_string(current) +
        " " + std::to_string(best));
        Restart();
        time = 0;
        era++;
    }
}
