#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <Model.hpp>
#include <cmath>

#include "DFComponent.hpp"

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

class EraComponent: public DFComponent
{

private:
    std::vector<DFEntity*> stickmans;
    int era;
    int time;
    int best;
    int multi;

public:
    EraComponent(std::vector<DFEntity*> stickmans): stickmans(stickmans){}
    void onInit(DFEntity &gameObject);
    void Restart();
    std::vector<Model*> GetModels();
    void Update();
};