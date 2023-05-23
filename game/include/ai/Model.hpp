#pragma once

#include "BaseModel.hpp"

class Model: public BaseModel
{

friend class Evolution;
friend class EraComponent;

public:
    Model(StickmanPhysicsComponent *stickman): BaseModel(stickman) {}
    Model(StickmanPhysicsComponent *stickman, std::string file): BaseModel(stickman, file) {}
    std::array<float, OUT_DIM> predict();
    void updateRecord();
    float getRecord() const;
    void resetRecord();
    bool getActive() const;

private:
    bool active;
    float best_record;

};