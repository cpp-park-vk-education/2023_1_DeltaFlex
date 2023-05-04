#include <gtest/gtest.h>
#include "PointMass.hpp"

TEST(PointMassTest, test_applyNoForce)
{
    PointMass pm({40, 40}, 1, 10);
    Vector2<float> oldPos = pm.m_pos;

    pm.applyForce({0, 0});

    EXPECT_EQ(pm.m_pos.x, oldPos.x);
    EXPECT_EQ(pm.m_pos.y, oldPos.y);
}
