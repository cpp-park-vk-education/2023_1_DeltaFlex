#pragma once

#include <iostream>
#include <vector>
#include <Model.hpp>

class Model;

class Evolution
{

private:
    std::vector<Model*> models;
    size_t best_count;
    void Crossing_One(Model *child, Model *parent1, Model *parent2);

public:
    Evolution(std::vector<Model*> models);
    void Selection();
    void Crossing();
    void Mutation();
    size_t getBestCount();
    std::vector<Model*> getModels(int k);

};