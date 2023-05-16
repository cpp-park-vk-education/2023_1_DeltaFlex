#include <gtest/gtest.h>
#include "StickmanCircle.hpp"

TEST(StickmanCircleTest, test_solveConstraintsLess)
{
    StickmanCircle c(10, {-1, -1});

    c.solveConstraints(1280, 720);

    EXPECT_GE(c.m_attachedPointMass->m_pos.x, 0);
    EXPECT_GE(c.m_attachedPointMass->m_pos.y, 0);
}

TEST(StickmanCircleTest, test_solveConstraintsMore)
{
    StickmanCircle c(10, {1284, 721});

    c.solveConstraints(1280, 720);

    EXPECT_LE(c.m_attachedPointMass->m_pos.x, 1280);
    EXPECT_LE(c.m_attachedPointMass->m_pos.y, 720);
}
