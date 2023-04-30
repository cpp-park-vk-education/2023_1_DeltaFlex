#include <DFInputSystem.hpp>
#include <DFScene.hpp>
#include <DFWorldScene.hpp>
#include <DFEngine.hpp>
#include <DFComponent.hpp>
#include <spdlog/spdlog.h>
#include <DFTransform.hpp>
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
        // std::cout << "Nigger\n";
        Vector2<float> align(0, 475.873 - 100);
        // std::cout << my_stickman->m_stickmanCircles.size();
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

// class Model():
//     def __init__(self, stickman, active_func):
//         self.stickman = stickman
//         self.w1 = np.random.uniform(-1, 1, size=(INPUT_DIM, H_DIM))
//         self.b1 = np.random.uniform(-1, 1, size=(H_DIM))
//         self.w2 = np.random.uniform(-1, 1, size=(H_DIM, OUT_DIM))
//         self.b2 = np.random.uniform(-1, 1, size=(OUT_DIM))
//         self.active_func = active_func
//         self.best_record = 0

//     def set_stickman(self, stickman):
//         self.best_record = 0
//         self.stickman = stickman

//     def predict(self):
//         input_layout = stickman.get_coords()
//         inv_layout1 = self.active_func(input_layout @ self.w1 + self.b1)
//         result = self.active_func(inv_layout1 @ self.w2 + self.b2) / 10
//         stickman.move_all(result)

//     def update_record(self):
//         self.best_record += 100/self.stickman.pointmasses[0].y

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
const size_t H_DIM = 16;
const size_t OUT_DIM = 11;

class Model
{

public:
    Model(StickmanPhysicsComponent *stickman): best_record(0), stickman(stickman)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);

        for (int i = 0; i < INPUT_DIM; i++)
            for (int j = 0; j < H_DIM; j++)
                w1[i][j] = dis(gen);

        for (int i = 0; i < H_DIM; i++)
            b1[i] = dis(gen);

        for (int i = 0; i < H_DIM; i++)
            for (int j = 0; j < OUT_DIM; j++)
                w2[i][j] = dis(gen);

        for (int i = 0; i < OUT_DIM; i++)
            b2[i] = dis(gen);

    }

    void predict()
    {
        auto input_layout = stickman->GetCoords();
        auto inv_layout1 = matrixMultiplication(input_layout, w1);
        auto inv_layout2 = matrixAddition(inv_layout1, b1);
        auto inv_layout3 = activeFunc(inv_layout2);
        auto inv_layout4 = matrixMultiplication(inv_layout3, w2);
        auto inv_layout5 = matrixAddition(inv_layout4, b2);
        auto result = activeFunc(inv_layout5);

        stickman->MoveAll(result);
    }

private:
    std::array<std::array<float, H_DIM>, INPUT_DIM> w1;
    std::array<float, H_DIM> b1;
    std::array<std::array<float, OUT_DIM>, H_DIM> w2;
    std::array<float, OUT_DIM> b2;

    StickmanPhysicsComponent *stickman;
    float best_record;

};

class StickmanAI: public DFComponent
{
private:
    StickmanPhysicsComponent *my_stickman;
    Model *model;

public:
    void onInit(DFEntity &gameObject)
    {
        DFEngine::setWindowTitle("I HATE NEGATIVE, BE MORE POSITIVE");
        my_stickman = gameObject.getComponent<StickmanPhysicsComponent>();
        model = new Model(my_stickman);
    }

    void Update()
    {
        model->predict();
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


DFScene *default_scene(void)
{
    DFWorldScene *sc = new DFWorldScene();

    for (int i = 0; i < 10; i++)
    {
        DFEntity &stickman = sc->addNewObject("stickman_" + std::to_string(i));
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.addComponent(new StickmanRestarter());
        stickman.addComponent(new StickmanAI());
        // stickman.transform.position.x = 50;
        // stickman.transform.position.y = 50;
        stickman.onInit();
        stickman.getComponent<StickmanRestarter>()->RestartStickman();
        // std::cout << "after construction" << &stickman;
    }

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
