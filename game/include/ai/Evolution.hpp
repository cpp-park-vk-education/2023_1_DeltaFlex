#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <Model.hpp>
#include <cmath>

class Model;

class Evolution
{

private:
    std::vector<Model*> models;
    size_t best_count;
    void Crossing_One(Model *child, Model *parent1, Model *parent2);

public:
    Evolution(std::vector<Model*> models);
    void Selection_Best();
    void Selection_Tournament(size_t tours, size_t max_members);
    void Crossing();
    void Mutation(float n, float procent);
    size_t getBestCount();
    std::vector<Model*> getModels(int k);

};