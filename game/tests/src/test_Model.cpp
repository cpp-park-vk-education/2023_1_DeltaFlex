#include <DFWorldScene.hpp>
#include <DFComponent.hpp>
#include "PhysicsComponent.hpp"
#include <gtest/gtest.h>
#include "Model.hpp"

TEST(ModelTest, test_predictResult)
{
    DFWorldScene *sc = new DFWorldScene();
    DFEntity &stickman = sc->addNewObject("stickman");
    stickman.addComponent(new StickmanPhysicsComponent());
    stickman.onInit();

    auto my_stickman = stickman.getComponent<StickmanPhysicsComponent>();
    auto model = new Model(my_stickman);

    auto test_res = model->predict();

    std::array<float, 11> res = {-0.103591, 0.604108, -0.986522, -0.997239, 0.971981, -0.5389, 0.903677, 0.916517, -0.162188, 0.974992, -0.864615};

    for (int i = 0; i < 11; i++)
    {
        EXPECT_NEAR(res[i], test_res[i], 1e-5);
    }
}

TEST(ModelTest, test_predictRange)
{
    DFWorldScene *sc = new DFWorldScene();
    DFEntity &stickman = sc->addNewObject("stickman");
    stickman.addComponent(new StickmanPhysicsComponent());
    stickman.onInit();

    auto my_stickman = stickman.getComponent<StickmanPhysicsComponent>();
    auto model = new Model(my_stickman);

    auto res = model->predict();

    for (int i = 0; i < 11; i++)
    {
        EXPECT_LE(abs(res[i]), 1);
    }
}

TEST(ModelTest, test_initRecord)
{
    DFWorldScene *sc = new DFWorldScene();
    DFEntity &stickman = sc->addNewObject("stickman");
    stickman.addComponent(new StickmanPhysicsComponent());
    stickman.onInit();

    auto my_stickman = stickman.getComponent<StickmanPhysicsComponent>();
    auto model = new Model(my_stickman);

    EXPECT_NEAR(model->getRecord(), 0, 1e-5);
}

TEST(ModelTest, test_updateRecord)
{
    DFWorldScene *sc = new DFWorldScene();
    DFEntity &stickman = sc->addNewObject("stickman");
    stickman.addComponent(new StickmanPhysicsComponent());
    stickman.onInit();

    auto my_stickman = stickman.getComponent<StickmanPhysicsComponent>();
    auto model = new Model(my_stickman);

    for (int i = 0; i < 100; i++)
        model->updateRecord();

    EXPECT_GT(model->getRecord(), 0);
}


TEST(ModelTest, test_resetRecord)
{
    DFWorldScene *sc = new DFWorldScene();
    DFEntity &stickman = sc->addNewObject("stickman");
    stickman.addComponent(new StickmanPhysicsComponent());
    stickman.onInit();

    auto my_stickman = stickman.getComponent<StickmanPhysicsComponent>();
    auto model = new Model(my_stickman);

    for (int i = 0; i < 100; i++)
        model->updateRecord();
    model->resetRecord();

    EXPECT_NEAR(model->getRecord(), 0, 1e-5);
}
