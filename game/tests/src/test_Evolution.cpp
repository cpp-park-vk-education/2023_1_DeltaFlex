#include <DFWorldScene.hpp>
#include <DFComponent.hpp>
#include "PhysicsComponent.hpp"
#include <gtest/gtest.h>
#include "Evolution.hpp"
#include "ControlComponents.hpp"

TEST(EvolutionTest, test_selectionCountOne)
{
    DFWorldScene *sc = new DFWorldScene();
    std::vector<Model*> stickmans;

    for (int i = 0; i < 1; i++)
    {
        DFEntity &stickman = sc->addNewObject("stickman_" + std::to_string(i));
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.onInit();

        auto my_stickman = stickman.getComponent<StickmanPhysicsComponent>();
        auto model = new Model(my_stickman);
        stickmans.push_back(model);
    }

    Evolution evo(stickmans);

    evo.Selection();
    evo.getBestCount();

    EXPECT_EQ(evo.getBestCount(), 1);
}

TEST(EvolutionTest, test_selectionCountNotSquare)
{
    DFWorldScene *sc = new DFWorldScene();
    std::vector<Model*> stickmans;

    for (int i = 0; i < 44; i++)
    {
        DFEntity &stickman = sc->addNewObject("stickman_" + std::to_string(i));
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.onInit();

        auto my_stickman = stickman.getComponent<StickmanPhysicsComponent>();
        auto model = new Model(my_stickman);
        stickmans.push_back(model);
    }

    Evolution evo(stickmans);

    evo.Selection();
    evo.getBestCount();

    EXPECT_EQ(evo.getBestCount(), 7);
}

TEST(EvolutionTest, test_selectionCountSquare)
{
    DFWorldScene *sc = new DFWorldScene();
    std::vector<Model*> stickmans;

    for (int i = 0; i < 100; i++)
    {
        DFEntity &stickman = sc->addNewObject("stickman_" + std::to_string(i));
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.onInit();

        auto my_stickman = stickman.getComponent<StickmanPhysicsComponent>();
        auto model = new Model(my_stickman);
        stickmans.push_back(model);
    }

    Evolution evo(stickmans);

    evo.Selection();
    evo.getBestCount();

    EXPECT_EQ(evo.getBestCount(), 10);
}

TEST(EvolutionTest, test_selectionBest)
{
    DFWorldScene *sc = new DFWorldScene();
    std::vector<Model*> stickmans;

    for (int i = 0; i < 44; i++)
    {
        DFEntity &stickman = sc->addNewObject("stickman_" + std::to_string(i));
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.addComponent(new StickmanRestarter());
        stickman.onInit();

        auto my_stickman = stickman.getComponent<StickmanPhysicsComponent>();
        auto model = new Model(my_stickman);
        stickman.getComponent<StickmanRestarter>()->RestartStickman();

        model->updateRecord();
        stickmans.push_back(model);
    }

    Evolution evo(stickmans);
    evo.Selection();
    auto res = evo.getModels(1)[0]->getRecord();

    EXPECT_NEAR(res, 0.835581, 1e-5);
}

TEST(EvolutionTest, test_crossingBest)
{
    DFWorldScene *sc = new DFWorldScene();
    std::vector<Model*> stickmans;

    for (int i = 0; i < 100; i++)
    {
        DFEntity &stickman = sc->addNewObject("stickman_" + std::to_string(i));
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.addComponent(new StickmanRestarter());
        stickman.onInit();

        auto my_stickman = stickman.getComponent<StickmanPhysicsComponent>();
        auto model = new Model(my_stickman);
        stickman.getComponent<StickmanRestarter>()->RestartStickman();

        model->updateRecord();
        stickmans.push_back(model);
    }

    Evolution evo(stickmans);
    evo.Selection();
    auto models1 = evo.getModels(10);
    evo.Crossing();
    auto models2 = evo.getModels(10);

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(models1[i], models2[i]);
    }
}

TEST(EvolutionTest, test_crossingAll)
{
    DFWorldScene *sc = new DFWorldScene();
    std::vector<Model*> stickmans;

    for (int i = 0; i < 100; i++)
    {
        DFEntity &stickman = sc->addNewObject("stickman_" + std::to_string(i));
        stickman.addComponent(new StickmanPhysicsComponent());
        stickman.addComponent(new StickmanRestarter());
        stickman.onInit();

        auto my_stickman = stickman.getComponent<StickmanPhysicsComponent>();
        auto model = new Model(my_stickman);
        stickman.getComponent<StickmanRestarter>()->RestartStickman();

        model->updateRecord();
        stickmans.push_back(model);
    }

    Evolution evo(stickmans);
    evo.Selection();
    int k = evo.getBestCount();
    evo.Crossing();
    auto models = evo.getModels(k*k);
    EXPECT_EQ(models.size(), k*k);
}