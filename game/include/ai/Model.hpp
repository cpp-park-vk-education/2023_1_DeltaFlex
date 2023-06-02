#pragma once

#include "BaseModel.hpp"
#include <array>
#include <iostream>
#include <random>
#include <iostream>
#include <fstream>
#include <string>

#include "MatrixActions.hpp"
#include "PhysicsComponent.hpp"
class StickmanPhysicsComponent;

class Model: public BaseModel
{

static const size_t INPUT_DIM = 12;
static const size_t H_DIM1 = 32;
static const size_t H_DIM2 = 20;
static const size_t H_DIM3 = 12;
static const size_t OUT_DIM = 6;

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
    void save(int stage, int current) override;
    void load(std::string file) override;

private:
    std::array<std::array<float, H_DIM1>, INPUT_DIM> w1;
    std::array<float, H_DIM1> b1;
    std::array<std::array<float, H_DIM2>, H_DIM1> w2;
    std::array<float, H_DIM2> b2;
    std::array<std::array<float, H_DIM3>, H_DIM2> w3;
    std::array<float, H_DIM3> b3;
    std::array<std::array<float, OUT_DIM>, H_DIM3> w4;
    std::array<float, OUT_DIM> b4;

    bool active;
    float best_record;
    StickmanPhysicsComponent *stickman;

};