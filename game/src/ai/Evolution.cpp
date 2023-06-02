#include "Evolution.hpp"
#include <DFEntity.hpp>
#include <ControlComponents.hpp>
Evolution::Evolution(std::vector<Model*> models): models(models), best_count(0) {}

void Evolution::Crossing_One(Model *child, Model *parent1, Model *parent2)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1000);

    int i_c = dist(gen) % parent1->w1.size();
    int j_c = dist(gen) % parent1->w1[0].size();
    for (size_t i = 0; i < parent1->w1.size(); i++)
    {
        for (size_t j = 0; j < parent1->w1[0].size(); j++)
        {
            child->w1[i][j] = ((i == i_c || j < j_c) || i < i_c) ? parent1->w1[i][j] : parent2->w1[i][j];
        }
    }

    i_c = dist(gen) % parent1->b1.size();
    for (size_t i = 0; i < parent1->b1.size(); i++)
    {
        child->b1[i] = (i < i_c) ? parent1->b1[i] : parent2->b1[i];
    }

    i_c = dist(gen) % parent1->w2.size();
    j_c = dist(gen) % parent1->w2[0].size();
    for (size_t i = 0; i < parent1->w2.size(); i++)
    {
        for (size_t j = 0; j < parent1->w2[0].size(); j++)
        {
            child->w2[i][j] = ((i == i_c || j < j_c) || i < i_c) ? parent1->w2[i][j] : parent2->w2[i][j];
        }
    }

    i_c = dist(gen) % parent1->b2.size();
    for (size_t i = 0; i < parent1->b2.size(); i++)
    {
        child->b2[i] = (i < i_c) ? parent1->b2[i] : parent2->b2[i];
    }

    i_c = dist(gen) % parent1->w3.size();
    j_c = dist(gen) % parent1->w3[0].size();
    for (size_t i = 0; i < parent1->w3.size(); i++)
    {
        for (size_t j = 0; j < parent1->w3[0].size(); j++)
        {
            child->w3[i][j] = ((i == i_c || j < j_c) || i < i_c) ? parent1->w3[i][j] : parent2->w3[i][j];
        }
    }

    i_c = dist(gen) % parent1->b3.size();
    for (size_t i = 0; i < parent1->b3.size(); i++)
    {
        child->b3[i] = (i < i_c) ? parent1->b3[i] : parent2->b3[i];
    }

    i_c = dist(gen) % parent1->w4.size();
    j_c = dist(gen) % parent1->w4[0].size();
    for (size_t i = 0; i < parent1->w4.size(); i++)
    {
        for (size_t j = 0; j < parent1->w4[0].size(); j++)
        {
            child->w4[i][j] = ((i == i_c || j < j_c) || i < i_c) ? parent1->w4[i][j] : parent2->w4[i][j];
        }
    }

    i_c = dist(gen) % parent1->b4.size();
    for (size_t i = 0; i < parent1->b4.size(); i++)
    {
        child->b4[i] = (i < i_c) ? parent1->b4[i] : parent2->b4[i];
    }
}

void Evolution::Selection_Best()
{
    best_count = static_cast<size_t>(std::ceil(sqrt(models.size())));
    std::sort(models.begin(), models.end(), [](Model* a, Model* b){
        return a->best_record > b->best_record;
    });
}

void Evolution::Selection_Tournament(size_t tours, size_t max_members)
{
    best_count = static_cast<size_t>(std::ceil(sqrt(models.size())));
    size_t current_size = models.size();
    std::mt19937 gen(232);
    for (size_t tour = 0; tour < tours; tour++)
    {
        size_t group_count = ceil(current_size / static_cast<float>(max_members));
        if (group_count < best_count)
        {
            group_count = best_count;
            max_members = ceil(current_size / static_cast<float>(group_count));
        }
        std::uniform_int_distribution<> dist(0, group_count-1);
        std::vector<std::vector<size_t>> groups(group_count);

        for (size_t i = 0; i < current_size; i++)
        {
            if (i < group_count)
            {
                size_t cur = dist(gen);
                while (!groups[cur].empty())
                    cur = dist(gen);
                groups[cur].push_back(i);
            }
            else
            {
                size_t cur = dist(gen);
                while (groups[cur].size() >= max_members)
                    cur = dist(gen);
                groups[cur].push_back(i);
            }
        }

        current_size = group_count;

        for (auto &group: groups)
        {
            while (group.size() > 1)
            {
                if (models[group[0]]->getRecord() < models[group[1]]->getRecord())
                {
                    group.erase(group.begin());
                }
                else
                {
                    group.erase(++group.begin());
                }
            }
        }

        for (auto group = groups.rbegin(); group != --groups.rend(); group++)
        {
            groups[0].push_back(group->at(0));
            groups.pop_back();
        }

        std::sort(groups[0].begin(), groups[0].end());
    
        for (size_t i = 0; i < group_count; i++)
            std::swap(models[i], models[groups[0][i]]);
    }
}

void Evolution::Crossing()
{
    size_t k = 0;
    for (size_t i = 0; i < best_count - 1; i++)
    {
        for (size_t j = i + 1; j < best_count; j++)
        {
            Crossing_One(models[best_count+k], models[i], models[j]);
            k++;
            if (best_count + k >= models.size())
                return;
            Crossing_One(models[best_count+k], models[j], models[i]);
            k++;
            if (best_count + k >= models.size())
                return;
        }
    }
    
}

void Evolution::Mutation(float n, float procent)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 99);
    std::uniform_real_distribution<> dis(-1.0 * n, 1.0 * n);

    for (size_t i = 0; i < models.size(); i++)
    {
        if (dist(gen) % 100 < procent)
        {
            int num = dist(gen);
            if (num < 100 / 8)
            {
                int i_c = dist(gen) % models[i]->w1.size();
                int j_c = dist(gen) % models[i]->w1[0].size();
                models[i]->w1[i_c][j_c] += dis(gen);
            }
            else if (num < 200 / 8)
            {
                int i_c = dist(gen) % models[i]->b1.size();
                models[i]->b1[i_c] += dis(gen);
            }
            else if (num < 300 / 8)
            {
                int i_c = dist(gen) % models[i]->w2.size();
                int j_c = dist(gen) % models[i]->w2[0].size();
                models[i]->w2[i_c][j_c] += dis(gen);
            }
            else if (num < 400 / 8)
            {
                int i_c = dist(gen) % models[i]->b2.size();
                models[i]->b2[i_c] += dis(gen);
            }
            else if (num < 500 / 8)
            {
                int i_c = dist(gen) % models[i]->w2.size();
                int j_c = dist(gen) % models[i]->w2[0].size();
                models[i]->w2[i_c][j_c] += dis(gen);
            }
            else if (num < 600 / 8)
            {
                int i_c = dist(gen) % models[i]->b2.size();
                models[i]->b2[i_c] += dis(gen);
            }
            else if (num < 700 / 8)
            {
                int i_c = dist(gen) % models[i]->w3.size();
                int j_c = dist(gen) % models[i]->w3[0].size();
                models[i]->w3[i_c][j_c] += dis(gen);
            }
            else
            {
                int i_c = dist(gen) % models[i]->b3.size();
                models[i]->b3[i_c] += dis(gen);
            }
        }
    }
}

std::vector<Model*> Evolution::getModels(int k)
{
    std::vector<Model*> models_k;
    for (size_t i = 0; i < k; i++)
    {
        models_k.push_back(models[i]);
    }
    return models_k;
}


size_t Evolution::getBestCount()
{
    return best_count;
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
        stickmans[i]->getComponent<StickmanAI>()->idle_model->resetRecord();
    }
}

std::vector<Model*> EraComponent::GetModels()
{
    std::vector<Model*> models;
    for (size_t i = 0; i < stickmans.size(); i++)
    {
        stickmans[i]->getComponent<StickmanAI>()->battle_action = 0;
        models.push_back(stickmans[i]->getComponent<StickmanAI>()->idle_model);
    }
    return models;
}

void EraComponent::Update()
{
    auto models = GetModels();
    for (auto &model: models)
    {
        model->updateRecord();
    }

    bool active = false;
    for (auto &model: models)
    {
        if (model->getActive())
        {
            active = true;
            break;
        }
    }
    
    int time_restart = 300;
    
    if (!active)
        time = time_restart;
    
    time++;
    if (time > time_restart)
    {
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
            evo.Selection_Best();
            evo.Crossing();
            evo.Mutation(1, 100);
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
