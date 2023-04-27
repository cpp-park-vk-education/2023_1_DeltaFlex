#pragma once

template<typename T>
struct Vector2
{
    T x, y;
    Vector2(): x(0), y(0) {}
    Vector2(T x_, T y_): x(x_), y(y_) {}
    Vector2<T> operator+(const Vector2<T> &other)
    {
        return Vector2<T>(x + other.x, y + other.y);
    }
    Vector2<T> operator-(const Vector2<T> &other)
    {
        return Vector2<T>(x - other.x, y - other.y);
    }
};
