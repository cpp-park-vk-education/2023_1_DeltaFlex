#pragma once

template<typename T>
struct DFvec2
{
    T x, y;
    DFvec2(): x(0), y(0) {}
    DFvec2(T x_, T y_): x(x_), y(y_) {}
    auto operator+(const DFvec2<T> &other)
    {
        return DFvec2<T>(x + other.x, y + other.y);
    }
    auto operator-(const DFvec2<T> &other)
    {
        return DFvec2<T>(x - other.x, y - other.y);
    }
};
