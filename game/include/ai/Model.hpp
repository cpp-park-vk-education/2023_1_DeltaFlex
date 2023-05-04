#pragma once

#include <array>
#include <iostream>
#include <random>

#include "Evolution.hpp"
#include "PhysicsComponent.hpp"
#include "MatrixActions.hpp"

const size_t INPUT_DIM = 22;
const size_t H_DIM1 = 20;
const size_t H_DIM2 = 16;
const size_t OUT_DIM = 11;

class Model
{

friend class Evolution;

public:
    Model(StickmanPhysicsComponent *stickman);
    std::array<float, OUT_DIM> predict();
    void updateRecord();
    float getRecord() const;
    void resetRecord();

private:
    std::array<std::array<float, H_DIM1>, INPUT_DIM> w1;
    std::array<float, H_DIM1> b1;
    std::array<std::array<float, H_DIM2>, H_DIM1> w2;
    std::array<float, H_DIM2> b2;
    std::array<std::array<float, OUT_DIM>, H_DIM2> w3;
    std::array<float, OUT_DIM> b3;

    StickmanPhysicsComponent *stickman;
    float best_record;

};