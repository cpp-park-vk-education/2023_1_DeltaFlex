#include "Model.hpp"

Model::Model(StickmanPhysicsComponent *stickman): best_record(0), stickman(stickman)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.0, 10.0);

    for (int i = 0; i < INPUT_DIM; i++)
        for (int j = 0; j < H_DIM1; j++)
            w1[i][j] = dis(gen);

    for (int i = 0; i < H_DIM1; i++)
        b1[i] = dis(gen);

    for (int i = 0; i < H_DIM1; i++)
        for (int j = 0; j < H_DIM2; j++)
            w2[i][j] = dis(gen);

    for (int i = 0; i < H_DIM2; i++)
        b2[i] = dis(gen);
    
    for (int i = 0; i < H_DIM2; i++)
        for (int j = 0; j < H_DIM3; j++)
            w3[i][j] = dis(gen);

    for (int i = 0; i < H_DIM3; i++)
        b3[i] = dis(gen);
    
    for (int i = 0; i < H_DIM3; i++)
        for (int j = 0; j < OUT_DIM; j++)
            w4[i][j] = dis(gen);

    for (int i = 0; i < OUT_DIM; i++)
        b4[i] = dis(gen);

}

std::array<float, OUT_DIM> Model::predict()
{
    auto input_layout = stickman->GetCoords();

    auto inv_layout1 = matrixMultiplication(input_layout, w1);
    auto inv_layout2 = matrixAddition(inv_layout1, b1);
    auto inv_layout3 = activeFunc(inv_layout2);

    auto inv_layout4 = matrixMultiplication(inv_layout3, w2);
    auto inv_layout5 = matrixAddition(inv_layout4, b2);
    auto inv_layout6 = activeFunc(inv_layout5);

    auto inv_layout7 = matrixMultiplication(inv_layout6, w3);
    auto inv_layout8 = matrixAddition(inv_layout7, b3);
    auto inv_layout9 = activeFunc(inv_layout8);

    auto inv_layout10 = matrixMultiplication(inv_layout9, w4);
    auto inv_layout11 = matrixAddition(inv_layout10, b4);
    auto result = activeFunc(inv_layout11);
    
    return result;
}

void Model::updateRecord()
{
    if (stickman->m_pointMasses[0]->m_pos.y > 700)
        active = false;
    if (active)
        best_record += 50 +
        (stickman->m_pointMasses[10]->m_pos.y - stickman->m_pointMasses[2]->m_pos.y) +
        (stickman->m_pointMasses[9]->m_pos.y - stickman->m_pointMasses[2]->m_pos.y);
}

float Model::getRecord() const
{
    return best_record;
}

void Model::resetRecord()
{
    active = true;
    best_record = 0;
}

bool Model::getActive() const
{
    return active;
}
