#include <iostream>
#include <functional>
#include <vector>
#include <queue>
template<typename Signature>
class DFTimer
{
private:
    int m_counter;
    std::queue<std::pair<int, std::function<Signature>>> m_callbacks;

public:
    DFTimer() { ResetTimer(); }
    void ResetTimer() { m_counter = 0; }
    void AddOnceCallback(std::function<Signature> func, int ticks)
    {
        m_callbacks.push(std::pair<int, std::function<Signature>>(ticks, func));
    }

    void Update()
    {
        ++m_counter;

        while(!m_callbacks.empty() && --m_callbacks.front().first < 0)
        {
            m_callbacks.front().second();
            m_callbacks.pop();
        }
    }
};

void print_hello()
{
    std::cout << "Hello\n";
}

int main(void)
{
    DFTimer<void()> timer;
    timer.AddOnceCallback(print_hello, 2);
    timer.AddOnceCallback(print_hello, 2);
    timer.AddOnceCallback(print_hello, 2);
    timer.AddOnceCallback(print_hello, 0);
    timer.AddOnceCallback(print_hello, 0);
    timer.AddOnceCallback(print_hello, 0);
    for(size_t i = 0; i < 20; ++i)
    {
        std::cout << "TICK: " << i << std::endl;
        timer.Update();
    }
    // std::function<void()> test;
    // test = std::bind(&DFTimer<void()>::ResetTimer, &timer);
    // test();
    return 0;
}