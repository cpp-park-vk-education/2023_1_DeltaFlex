#include "Evolution.hpp"

Evolution::Evolution(std::vector<Model*> models): models(models), best_count(0) {}

void Evolution::Crossing_One(Model *child, Model *parent1, Model *parent2)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    // std::uniform_real_distribution<> dis(-10.0, 10.0);
    std::uniform_int_distribution<> dist(0, 1000);

    int i_c = dist(gen) % parent1->w1.size();
    int j_c = dist(gen) % parent1->w1[0].size();
    for (size_t i = 0; i < parent1->w1.size(); i++)
    {
        for (size_t j = 0; j < parent1->w1[0].size(); j++)
        {
            child->w1[i][j] = (i < i_c || j < j_c) ? parent1->w1[i][j] : parent2->w1[i][j];
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
            child->w2[i][j] = (i < i_c || j < j_c) ? parent1->w2[i][j] : parent2->w2[i][j];
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
            child->w3[i][j] = (i < i_c || j < j_c) ? parent1->w3[i][j] : parent2->w3[i][j];
        }
    }

    i_c = dist(gen) % parent1->b3.size();
    for (size_t i = 0; i < parent1->b3.size(); i++)
    {
        child->b3[i] = (i < i_c) ? parent1->b3[i] : parent2->b3[i];
    }
}

void Evolution::Selection()
{
    best_count = static_cast<size_t>(std::ceil(sqrt(models.size())));
    std::sort(models.begin(), models.end(), [](Model* a, Model* b){
        return a->best_record > b->best_record;
    });
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

void Evolution::Mutation()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10000);
    std::uniform_real_distribution<> dis(-100.0, 100.0);
    int count = dist(gen) % (models.size() - 10);
    int procent = 50;

    for (size_t i = 10; i < count; i++)
    {
        if (dist(gen) % 100 < procent)
        {
            int i_c = dist(gen) % models[i]->w1.size();
            int j_c = dist(gen) % models[i]->w1[0].size();
            models[i]->w1[i_c][j_c] = dis(gen);
        }

        if (dist(gen) % 100 <= procent)
        {
            int i_c = dist(gen) % models[i]->b1.size();
            models[i]->b1[i_c] = dis(gen);
        }

        if (dist(gen) % 100 <= procent)
        {
            int i_c = dist(gen) % models[i]->w2.size();
            int j_c = dist(gen) % models[i]->w2[0].size();
            models[i]->w2[i_c][j_c] = dis(gen);
        }

        if (dist(gen) % 100 <= procent)
        {
            int i_c = dist(gen) % models[i]->b2.size();
            models[i]->b2[i_c] = dis(gen);
        }

        if (dist(gen) % 100 <= procent)
        {
            int i_c = dist(gen) % models[i]->w3.size();
            int j_c = dist(gen) % models[i]->w3[0].size();
            models[i]->w3[i_c][j_c] = dis(gen);
        }

        if (dist(gen) % 100 <= procent)
        {
            int i_c = dist(gen) % models[i]->b3.size();
            models[i]->b3[i_c] = dis(gen);
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
