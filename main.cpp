#include <DFInputSystem.hpp>
#include <DFScene.hpp>
#include <DFWorldScene.hpp>
#include <DFEngine.hpp>
#include <DFComponent.hpp>
#include <spdlog/spdlog.h>
#include <DFTransform.hpp>
#include <iomanip>
// #include <DFPosition.hpp>
// #include <DFSprite.hpp>
// #include <DFCollider.hpp>
#include "PhysicsComponent.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <array>
#include <random>

class StickmanRestarter: public DFComponent
{
private:
    StickmanPhysicsComponent *my_stickman;

public:
    void onInit(DFEntity &gameObject)
    {
        my_stickman = gameObject.getComponent<StickmanPhysicsComponent>();
    }

    void Update()
    {
        if (Input::GetKeyDown(KEYCODE_R))
            RestartStickman();
    }

    void RestartStickman()
    {
        Vector2<float> align(-500, 475.873 - 20);
        my_stickman->m_pointMasses[0]->m_pos = align + Vector2<float>(619.665, 23.703);
        my_stickman->m_pointMasses[1]->m_pos = align + Vector2<float>(619.665, 43.6235);
        my_stickman->m_pointMasses[2]->m_pos = align + Vector2<float>(619.659, 137.391);
        my_stickman->m_pointMasses[3]->m_pos = align + Vector2<float>(619.63, 83.7396);
        my_stickman->m_pointMasses[4]->m_pos = align + Vector2<float>(619.669, 83.7609);
        my_stickman->m_pointMasses[5]->m_pos = align + Vector2<float>(619.554, 137.073);
        my_stickman->m_pointMasses[6]->m_pos = align + Vector2<float>(619.664, 137.094);
        my_stickman->m_pointMasses[7]->m_pos = align + Vector2<float>(619.704, 190.655);
        my_stickman->m_pointMasses[8]->m_pos = align + Vector2<float>(619.614, 190.794);
        my_stickman->m_pointMasses[9]->m_pos = align + Vector2<float>(619.774, 243.988);
        my_stickman->m_pointMasses[10]->m_pos = align + Vector2<float>(619.544, 244.127);
        for (auto &x : my_stickman->m_pointMasses)
        {
            x->m_acceleration = { 0, 0 };
            x->m_oldPos = x->m_pos;
        }
    }
};

template <typename T, size_t N, size_t M, size_t L>
std::array<std::array<T, L>, N> matrixMultiplication(
    std::array<std::array<T, M>, N> &a,
    std::array<std::array<T, L>, M> &b)
{
    std::array<std::array<T, L>, N> result{};
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < L; ++j)
        {
            for (size_t k = 0; k < M; ++k)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

template <typename T, size_t M, size_t L>
std::array<T, L> matrixMultiplication(
    std::array<T, M> &a,
    std::array<std::array<T, L>, M> &b)
{
    std::array<T, L> result{};
    for (size_t j = 0; j < L; ++j)
    {
        for (size_t k = 0; k < M; ++k)
        {
            result[j] += a[k] * b[k][j];
        }
    }
    return result;
}

template <typename T, size_t N, size_t M>
std::array<T, N> matrixMultiplication(
    std::array<std::array<T, M>, N> &a,
    std::array<T, M> &b)
{
    std::array<T, N> result{};
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t k = 0; k < M; ++k)
        {
            result[i] += a[i][k] * b[k];
        }
    }
    return result;
}

template <typename T, size_t N, size_t M>
std::array<std::array<T, M>, N> activeFunc(
    std::array<std::array<T, M>, N> &matrix)
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            matrix[i][j] = tanh(matrix[i][j]);
        }
    }
}

template <typename T, size_t N>
std::array<T, N> activeFunc(
    std::array<T, N> &matrix)
{
    std::array<T, N> result{};
    for (size_t i = 0; i < N; i++)
    {
        result[i] = tanh(matrix[i]);
    }
    return result;
}

template <typename T, size_t N, size_t M>
std::array<std::array<T, M>, N> matrixAddition(
    std::array<std::array<T, M>, N> &a,
    std::array<std::array<T, M>, N> &b)
{
    std::array<std::array<T, M>, N> result{};
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < M; ++j)
        {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    return result;
}

template <typename T, size_t N>
std::array<T, N> matrixAddition(
    std::array<T, N> &a,
    std::array<T, N> &b)
{
    std::array<T, N> result{};
    for (size_t i = 0; i < N; ++i)
    {
        result[i] = a[i] + b[i];
    }
    return result;
}

const size_t INPUT_DIM = 22;
const size_t H_DIM1 = 20;
const size_t H_DIM2 = 16;
const size_t OUT_DIM = 11;

class Evolution;

class Model
{

friend Evolution;

public:
    Model(StickmanPhysicsComponent *stickman): best_record(0), stickman(stickman)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);

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
            for (int j = 0; j < OUT_DIM; j++)
                w3[i][j] = dis(gen);

        for (int i = 0; i < OUT_DIM; i++)
            b3[i] = dis(gen);

    }

    void predict()
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
        auto result = activeFunc(inv_layout8);

        stickman->MoveAll(result);
    }

    void updateRecord()
    {
        best_record += 300/(stickman->m_pointMasses[0]->m_pos.x) - 100/(stickman->m_pointMasses[10]->m_pos.x) - 100/(stickman->m_pointMasses[9]->m_pos.x);
    }

    float getRecord() const
    {
        return best_record;
    }

    void resetRecord()
    {
        best_record = 0;
    }

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

class Evolution
{

private:
    std::vector<Model*> models;
    size_t best_count;

    void Crossing_One(Model *child, Model *parent1, Model *parent2)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        // std::uniform_real_distribution<> dis(-10.0, 10.0);
        std::uniform_int_distribution<> dist(0, 1000);

        int i_c = dist(gen) % parent1->w1.size();
        int j_c = dist(gen) % parent1->w1[0].size();
        for (size_t i = 0; i < parent1->w1.size(); i++)
        {
            for (size_t j = 0; j < parent1->w1[0].size(); j++)
            {
                child->w1[i][j] = (i < i_c || j < j_c) ? parent1->w1[i][j] : parent2->w1[i][j];
            }
        }

        i_c = dist(gen) % parent1->b1.size();
        for (size_t i = 0; i < parent1->b1.size(); i++)
        {
            child->b1[i] = (i < i_c) ? parent1->b1[i] : parent2->b1[i];
        }

        i_c = dist(gen) % parent1->w2.size();
        j_c = dist(gen) % parent1->w2[0].size();
        for (size_t i = 0; i < parent1->w2.size(); i++)
        {
            for (size_t j = 0; j < parent1->w2[0].size(); j++)
            {
                child->w2[i][j] = (i < i_c || j < j_c) ? parent1->w2[i][j] : parent2->w2[i][j];
            }
        }

        i_c = dist(gen) % parent1->b2.size();
        for (size_t i = 0; i < parent1->b2.size(); i++)
        {
            child->b2[i] = (i < i_c) ? parent1->b2[i] : parent2->b2[i];
        }

        i_c = dist(gen) % parent1->w3.size();
        j_c = dist(gen) % parent1->w3[0].size();
        for (size_t i = 0; i < parent1->w3.size(); i++)
        {
            for (size_t j = 0; j < parent1->w3[0].size(); j++)
            {
                child->w3[i][j] = (i < i_c || j < j_c) ? parent1->w3[i][j] : parent2->w3[i][j];
            }
        }

        i_c = dist(gen) % parent1->b3.size();
        for (size_t i = 0; i < parent1->b3.size(); i++)
        {
            child->b3[i] = (i < i_c) ? parent1->b3[i] : parent2->b3[i];
        }
    }

public:
    Evolution(std::vector<Model*> models): models(models), best_count(0) {}

    void Selection()
    {
        best_count = static_cast<size_t>(std::ceil(sqrt(models.size())));
        std::sort(models.begin(), models.end(), [](Model* a, Model* b){
            return a->best_record > b->best_record;
        });
    }

    void Crossing()
    {
        size_t k = 0;
        for (size_t i = 0; i < best_count - 1; i++)
        {
            for (size_t j = i + 1; j < best_count; j++)
            {
                Crossing_One(models[best_count+k], models[i], models[j]);
                k++;
                if (best_count + k >= models.size())
                    return;
                Crossing_One(models[best_count+k], models[j], models[i]);
                k++;
                if (best_count + k >= models.size())
                    return;
            }
        }
        
    }

    void Mutation()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 10000);
        std::uniform_real_distribution<> dis(-100.0, 100.0);
        int count = dist(gen) % (models.size() - 10);
        int procent = 50;

        for (size_t i = 10; i < count; i++)
        {
            if (dist(gen) % 100 < procent)
            {
                int i_c = dist(gen) % models[i]->w1.size();
                int j_c = dist(gen) % models[i]->w1[0].size();
                models[i]->w1[i_c][j_c] = dis(gen);
            }

            if (dist(gen) % 100 <= procent)
            {
                int i_c = dist(gen) % models[i]->b1.size();
                models[i]->b1[i_c] = dis(gen);
            }

            if (dist(gen) % 100 <= procent)
            {
                int i_c = dist(gen) % models[i]->w2.size();
                int j_c = dist(gen) % models[i]->w2[0].size();
                models[i]->w2[i_c][j_c] = dis(gen);
            }

            if (dist(gen) % 100 <= procent)
            {
                int i_c = dist(gen) % models[i]->b2.size();
                models[i]->b2[i_c] = dis(gen);
            }

            if (dist(gen) % 100 <= procent)
            {
                int i_c = dist(gen) % models[i]->w3.size();
                int j_c = dist(gen) % models[i]->w3[0].size();
                models[i]->w3[i_c][j_c] = dis(gen);
            }

            if (dist(gen) % 100 <= procent)
            {
                int i_c = dist(gen) % models[i]->b3.size();
                models[i]->b3[i_c] = dis(gen);
            }
        }
        
    }

    std::vector<Model*> getModels(int k)
    {
        std::vector<Model*> models_k;
        for (size_t i = 0; i < k; i++)
        {
            models_k.push_back(models[i]);
        }
        return models_k;
    }

};

class EraComponent;

class StickmanAI: public DFComponent
{

friend EraComponent;

private:
    StickmanPhysicsComponent *my_stickman;
    Model *model;

public:
    void onInit(DFEntity &gameObject)
    {
        my_stickman = gameObject.getComponent<StickmanPhysicsComponent>();
        model = new Model(my_stickman);
    }

    void Update()
    {
        model->predict();
        model->updateRecord();
    }
};

// class TestAbober: public DFComponent
// {
// private:
//     // DFTransform *transform;
//     std::vector<StickmanPhysicsComponent *> stickmans_physics;
//     std::vector<StickmanRestarter *> stickmans_restarters;

// public:
//     void Start()
//     {
//         stickmans_physics.reserve(10);
//         stickmans_restarters.reserve(10);
//         for (size_t i = 0; i < 1; ++i)
//         {
//             stickmans_physics[i] = DFEntity::Find("stickman_" + std::to_string(i))->getComponent<StickmanPhysicsComponent>();
//             stickmans_restarters[i] = DFEntity::Find("stickman_" + std::to_string(i))->getComponent<StickmanRestarter>();
//         }
//     }

//     void Update()
//     {
//         // std::cout << stickmans[0]<< std::endl;
//         // comp->m_stickmanCircles[0]->m_attachedPointMass->m_pos.x += Input::GetAxis(AXIS_HORIZONTAL) * 10;
//         StickmanCircle *left = stickmans_physics[0]->m_stickmanCircles[0].get();
//         left->m_attachedPointMass->m_pos.x += Input::GetAxis(AXIS_HORIZONTAL) * 10;
//         left->m_attachedPointMass->m_pos.y += Input::GetAxis(AXIS_VERTICAL) * 10;

//         // stickmans_restarters[0]->RestartStickman();

//         // left = comp2->m_stickmanCircles[0];
//         // left->m_attachedPointMass->m_pos.x += Input::GetAxis(AXIS_HORIZONTAL) * 10;
//         // left->m_attachedPointMass->m_pos.y += Input::GetAxis(AXIS_VERTICAL) * 10;

//         // auto &right = comp->m_pointMasses[50-1];
//         // right->m_pos.x = Input::GetMouseX();
//         // right->m_pos.y = Input::GetMouseY();
//     }
// };

class EraComponent: public DFComponent
{
private:
    std::vector<DFEntity*> stickmans;
    int era;
    int time;
    int best;

public:
    EraComponent(std::vector<DFEntity*> stickmans): stickmans(stickmans){}

    void onInit(DFEntity &gameObject)
    {
        era = 1;
        time = 0;
        best = 0;
        Restart();
    }

    void Restart()
    {
        for (size_t i = 0; i < stickmans.size(); i++)
        {
            stickmans[i]->getComponent<StickmanRestarter>()->RestartStickman();
            stickmans[i]->getComponent<StickmanAI>()->model->resetRecord();
        }
    }

    std::vector<Model*> GetModels()
    {
        std::vector<Model*> models;
        for (size_t i = 0; i < stickmans.size(); i++)
        {
            models.push_back(stickmans[i]->getComponent<StickmanAI>()->model);
        }
        return models;
    }

    void Update()
    {
        time++;
        if (time > 180)
        {
            Evolution evo(GetModels());
            evo.Selection();
            int current =  evo.getModels(1)[0]->getRecord();
            if (current > best)
                best = current;
            DFEngine::setWindowTitle(std::to_string(era) +
            " " + std::to_string(current) +
            " " + std::to_string(best));
            evo.Crossing();
            evo.Mutation();
            Restart();
            time = 0;
            era++;
        }
    }
};

DFScene *default_scene(void)
{
    DFWorldScene *sc = new DFWorldScene();
    std::vector<DFEntity*> stickmans;
    for (int i = 0; i < 100; i++)
    {
        DFEntity &stickman = sc->addNewObject("stickman_" + std::to_string(i));
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.addComponent(new StickmanRestarter());
        stickman.addComponent(new StickmanAI());
        stickmans.push_back(&stickman);
        // stickman.transform.position.x = 50;
        // stickman.transform.position.y = 50;
        stickman.onInit();
        // std::cout << "after construction" << &stickman;
    }

    DFEntity &era = sc->addNewObject("era");
    era.addComponent(new EraComponent(stickmans));
    era.onInit();

    // {
    //     DFEntity &stickman = sc->addNewObject("controller");
    //     stickman.addComponent(new TestAbober());
    //     stickman.onInit();
    // }

    // DFEntity &stickman1 = sc->addNewObject();
    // stickman1.addComponent(new StickmanPhysicsComponent());
    // stickman1.addComponent(new TestAbober());
    // stickman1.onInit();
    // // stickman2.addComponent(new TestAbober());
    // stickman2.getComponent<StickmanPhysicsComponent>()->m_stickmanCircles[0]->m_attachedPointMass->m_pos.x += 300;
    // stickman.addComponent(new PlayerControl());
    return sc;
}

int main(void)
{
    // DFEntity entity;
    // entity.addComponent(new DFSprite("./gears.png", entity.transform));
    // entity.addComponent(new DFCollider(entity.transform.position, Vector2<float>(12, 12), 1));
    // std::cout << entity.getComponent<DFCollider>() << std::endl;
    // entity.addComponent()
    // int a = 4;
    // std::cout << (typeid(int) == typeid(a));

    spdlog::set_level(spdlog::level::trace);
    std::unique_ptr<DFEngine> engine = std::make_unique<DFEngine>();

    engine->AppendSceneAllocator("default", default_scene);

    engine->EngineInit();
    engine->EngineCycle();
}
