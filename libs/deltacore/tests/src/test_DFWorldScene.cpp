#include <gtest/gtest.h>

#include "DFWorldScene.hpp"

TEST(TestDFWorldScene, empty_scene_create)
{
    DFWorldScene test;
    EXPECT_EQ(test.findEntity("test"), nullptr);
}

TEST(TestDFWorldScene, one_scene_object)
{
    DFWorldScene test;
    auto &obj = test.addNewObject("test");
    EXPECT_EQ(test.findEntity("test"), &obj);
    EXPECT_EQ(test.findEntity("other"), nullptr);
}

TEST(TestDFWorldScene, many_scene_object)
{
    DFWorldScene test;
    auto &obj1 = test.addNewObject("test_1");
    auto &obj2 = test.addNewObject("test_2");
    auto &obj3 = test.addNewObject("test_3");
    auto &obj4 = test.addNewObject("test_4");
    EXPECT_EQ(test.findEntity("test_3"), &obj3);
    EXPECT_EQ(test.findEntity("test_5"), nullptr);
}