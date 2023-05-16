#include <gtest/gtest.h>
#include "PointMass.hpp"

TEST(PointMassTest, test_applyNoForce)
{
    PointMass pm({40, 40}, 1, 10);
    Vector2<float> oldAcc = pm.m_acceleration;

    pm.applyForce({0, 0});

    EXPECT_EQ(pm.m_acceleration.x, oldAcc.x);
    EXPECT_EQ(pm.m_acceleration.y, oldAcc.y);
}

TEST(PointMassTest, test_applySomeForce)
{
    PointMass pm({40, 40}, 1, 10);

    pm.applyForce({0, 980});

    EXPECT_EQ(pm.m_acceleration.x, 0);
    EXPECT_EQ(pm.m_acceleration.y, 980);
}

TEST(PointMassTest, test_attachToEmptyList)
{
    PointMass pm1({40, 40}, 1, 10);
    PointMass pm2({40, 40}, 1, 5);

    pm1.attachTo(pm2, 10, 10, true);

    EXPECT_NE(pm1.links.size(), 0);
}

TEST(PointMassTest, test_attachToSomePMs)
{
    PointMass pm1({40, 40}, 1, 10);
    PointMass pm2({40, 40}, 1, 5);
    PointMass pm3({234, 40}, 1, 5);
    PointMass pm4({234, 40}, 1, 5);

    pm1.attachTo(pm2, 10, 10, true);
    pm1.attachTo(pm3, 10, 10, true);
    pm1.attachTo(pm4, 10, 10, true);

    EXPECT_EQ(pm1.links.size(), 3);
}

TEST(PointMassTest, test_solveConstraintsLess)
{
    PointMass pm1({-1, -1}, 1, 10);

    pm1.solveConstraints(1280, 720);

    EXPECT_GE(pm1.m_pos.x, 0);
    EXPECT_GE(pm1.m_pos.y, 0);
}

TEST(PointMassTest, test_solveConstraintsMore)
{
    PointMass pm1({1284, 724}, 1, 10);

    pm1.solveConstraints(1280, 720);

    EXPECT_GE(pm1.m_pos.x, 0);
    EXPECT_GE(pm1.m_pos.y, 0);
}
