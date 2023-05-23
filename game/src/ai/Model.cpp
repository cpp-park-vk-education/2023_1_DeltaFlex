#include "Model.hpp"
#include "PhysicsComponent.hpp"
#include "MatrixActions.hpp"

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
    if (stickman->m_pointMasses[0]->m_pos.y > 650)
        active = false;
    if (active)
        best_record +=
        (stickman->m_pointMasses[2]->m_pos.y - stickman->m_pointMasses[1]->m_pos.y) +
        (stickman->m_pointMasses[1]->m_pos.y - stickman->m_pointMasses[0]->m_pos.y);

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
