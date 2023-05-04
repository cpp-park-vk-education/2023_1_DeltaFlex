#include <gtest/gtest.h>
#include "Link.hpp"

TEST(LinkTest, test_solve)
{
    PointMass pm1({0, 0}, 1, 1);    
    PointMass pm2({0, 100}, 1, 1);

    Link l(pm1, pm2, 10, 10, true);

    auto oldLen = pm1.m_pos - pm2.m_pos;
    float dist = oldLen.length();

    l.solve();

    EXPECT_NE(l.length(), dist);
}
