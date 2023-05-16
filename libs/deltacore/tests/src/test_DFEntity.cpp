#include <gtest/gtest.h>
#include "DFEntity.hpp"

class TestComponentA : public DFComponent {};
class TestComponentB : public DFComponent {};

TEST(DFEntityTest, null_getcomponent)
{
    DFEntity test;
    EXPECT_EQ(test.getComponent<TestComponentA>(), nullptr);
}

TEST(DFEntityTest, nonnull_getcomponent)
{
    DFEntity test;
    TestComponentA *cmp = new TestComponentA();
    test.addComponent(cmp);
    EXPECT_EQ(test.getComponent<TestComponentA>(), cmp);
}

TEST(DFEntityTest, find_A_while_B_getcomponent)
{
    DFEntity test;
    TestComponentA *cmp = new TestComponentA();
    test.addComponent(cmp);
    EXPECT_EQ(test.getComponent<TestComponentB>(), nullptr);
}

TEST(DFEntityTest, find_B_while_B_getcomponent)
{
    DFEntity test;
    TestComponentA *cmp1 = new TestComponentA();
    TestComponentB *cmp2 = new TestComponentB();
    test.addComponent(cmp1);
    test.addComponent(cmp2);
    EXPECT_EQ(test.getComponent<TestComponentB>(), cmp2);
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

TEST(DFEntityTest, init_components)
{
    DFEntity test;
    int init_counter = 0, start_counter = 0, update_counter = 0;
    test.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    test.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    test.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    test.onInit();
    EXPECT_EQ(init_counter, 3);
    EXPECT_EQ(start_counter, 0);
    EXPECT_EQ(update_counter, 0);
}

TEST(DFEntityTest, start_components)
{
    DFEntity test;
    int init_counter = 0, start_counter = 0, update_counter = 0;
    test.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    test.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    test.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    test.onInit();
    test.Start();
    EXPECT_EQ(init_counter, 3);
    EXPECT_EQ(start_counter, 3);
    EXPECT_EQ(update_counter, 0);
}

TEST(DFEntityTest, update_components)
{
    DFEntity test;
    int init_counter = 0, start_counter = 0, update_counter = 0;
    test.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    test.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    test.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    test.onInit();
    test.Start();
    test.Update();
    EXPECT_EQ(init_counter, 3);
    EXPECT_EQ(start_counter, 3);
    EXPECT_EQ(update_counter, 3);
}

TEST(DFEntityTest, multiple_update_components)
{
    DFEntity test;
    int init_counter = 0, start_counter = 0, update_counter = 0;
    test.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    test.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    test.addComponent(new TestComponentWithCounter(init_counter, start_counter, update_counter));
    test.onInit();
    test.Start();
    for (size_t i = 0; i < 3; ++i)
    {
        test.Update();
    }
    EXPECT_EQ(init_counter, 3);
    EXPECT_EQ(start_counter, 3);
    EXPECT_EQ(update_counter, 3 * 3);
}