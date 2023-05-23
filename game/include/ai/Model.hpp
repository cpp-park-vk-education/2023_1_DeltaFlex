#pragma once

#include <array>
#include <iostream>
#include <random>
#include <iostream>
#include <fstream>
#include <string>

#include "ControlComponents.hpp"
#include "Evolution.hpp"
#include "PhysicsComponent.hpp"
#include "MatrixActions.hpp"

const size_t INPUT_DIM = 12;
const size_t H_DIM1 = 31;
const size_t H_DIM2 = 23;
const size_t H_DIM3 = 17;
const size_t OUT_DIM = 6;

class StickmanPhysicsComponent;

class Model
{

friend class Evolution;
friend class EraComponent;

public:
    Model(StickmanPhysicsComponent *stickman);
    Model(StickmanPhysicsComponent *stickman, std::string file);
    std::array<float, OUT_DIM> predict();
    void updateRecord();
    float getRecord() const;
    void resetRecord();
    bool getActive() const;
    void save(int stage, int current);
    void load(std::string file);

private:
    std::array<std::array<float, H_DIM1>, INPUT_DIM> w1;
    std::array<float, H_DIM1> b1;
    std::array<std::array<float, H_DIM2>, H_DIM1> w2;
    std::array<float, H_DIM2> b2;
    std::array<std::array<float, H_DIM3>, H_DIM2> w3;
    std::array<float, H_DIM3> b3;
    std::array<std::array<float, OUT_DIM>, H_DIM3> w4;
    std::array<float, OUT_DIM> b4;

    StickmanPhysicsComponent *stickman;
    bool active;
    float best_record;

};