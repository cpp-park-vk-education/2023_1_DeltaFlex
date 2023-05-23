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

Model::Model(StickmanPhysicsComponent *stickman, std::string file): best_record(0), stickman(stickman)
{
    load(file);
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
    auto result = matrixAddition(inv_layout10, b4);    
    


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

void Model::save(int stage, int current)
{
    std::ofstream output_file("../complete_models/model" + std::to_string(stage) + " " + std::to_string(current) + ".txt", std::ios::out);

    if (output_file.is_open()){

        for (const auto& row: w1) {
            for (const auto& val: row) {
                output_file << val << " ";
            }
        }
        output_file << std::endl;

        for (const auto& val : b1) {
            output_file << val << " ";
        }
        output_file << std::endl;

        for (const auto& row: w2) {
            for (const auto& val: row) {
                output_file << val << " ";
            }
        }
        output_file << std::endl;

        for (const auto& val : b2) {
            output_file << val << " ";
        }
        output_file << std::endl;

        for (const auto& row: w3) {
            for (const auto& val: row) {
                output_file << val << " ";
            }
        }
        output_file << std::endl;

        for (const auto& val : b3) {
            output_file << val << " ";
        }
        output_file << std::endl;

        for (const auto& row: w4) {
            for (const auto& val: row) {
                output_file << val << " ";
            }
        }
        output_file << std::endl;

        for (const auto& val : b4) {
            output_file << val << " ";
        }
        output_file << std::endl;

        output_file.close();
    }
    else {
        std::cout << "Не удалось открыть файл." << std::endl;
    }
}

void Model::load(std::string file)
{
    std::ifstream input_file(file);

    if (input_file.is_open()){

        for (size_t i = 0; i < w1.size(); i++) {
            for (size_t j = 0; j < w1[0].size(); j++) {
                input_file >> w1[i][j];
            }
        }

        for (size_t i = 0; i < b1.size(); i++) {
            input_file >> b1[i];
        }

        for (size_t i = 0; i < w2.size(); i++) {
            for (size_t j = 0; j < w2[0].size(); j++) {
                input_file >> w2[i][j];
            }
        }

        for (size_t i = 0; i < b2.size(); i++) {
            input_file >> b2[i];
        }

        for (size_t i = 0; i < w3.size(); i++) {
            for (size_t j = 0; j < w3[0].size(); j++) {
                input_file >> w3[i][j];
            }
        }

        for (size_t i = 0; i < b3.size(); i++) {
            input_file >> b3[i];
        }

        for (size_t i = 0; i < w4.size(); i++) {
            for (size_t j = 0; j < w4[0].size(); j++) {
                input_file >> w4[i][j];
            }
        }

        for (size_t i = 0; i < b4.size(); i++) {
            input_file >> b4[i];
        }
    }
    else {
        std::cout << "Не удалось открыть файл." << std::endl;
    }
}
