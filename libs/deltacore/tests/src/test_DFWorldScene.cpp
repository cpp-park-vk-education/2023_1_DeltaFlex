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

class TestComponentWithCounter : public DFComponent
{
public:
    int &init_counter;
    int &start_counter;
    int &update_counter;
    TestComponentWithCounter(int &a, int &b, int &c) : init_counter(a), start_counter(b), update_counter(c) {}

    void onInit(DFEntity &gameObject) { ++init_counter; }
    void Start() { ++start_counter; }
    void Update() { ++update_counter; }
};

TEST(TestDFWorldScene, scene_start)
{
    int init_counter = 0, start_counter = 0, update_counter = 0;
    DFWorldScene test;
    auto &obj1 = test.addNewObject("test_1");
    obj1.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    auto &obj2 = test.addNewObject("test_2");
    obj2.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    auto &obj3 = test.addNewObject("test_3");
    obj3.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    auto &obj4 = test.addNewObject("test_4");
    obj4.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));

    DFScUpdParams_t render_data;
    test.onSceneStart(render_data.render_system);
    EXPECT_EQ(init_counter, 0);
    EXPECT_EQ(start_counter, 4);
    EXPECT_EQ(update_counter, 0);
}

TEST(TestDFWorldScene, scene_update)
{
    int init_counter = 0, start_counter = 0, update_counter = 0;
    DFWorldScene test;
    auto &obj1 = test.addNewObject("test_1");
    obj1.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    auto &obj2 = test.addNewObject("test_2");
    obj2.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    auto &obj3 = test.addNewObject("test_3");
    obj3.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    auto &obj4 = test.addNewObject("test_4");
    obj4.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));

    DFScUpdParams_t render_data;
    test.onSceneStart(render_data.render_system);
    test.onHandleFrame(render_data.render_system);
    EXPECT_EQ(init_counter, 0);
    EXPECT_EQ(start_counter, 4);
    EXPECT_EQ(update_counter, 4);
}