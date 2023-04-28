#pragma once
#include <cmath>

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

    Vector2 &operator+=(const Vector2<T> &other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    Vector2 &operator+=(Vector2<T> &&other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    Vector2<T> operator-(const Vector2<T> &other)
    {
        return Vector2<T>(x - other.x, y - other.y);
    }

    Vector2 &operator-=(const Vector2<T> &other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    Vector2 &operator-=(Vector2<T> &&other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    // --------------------- multiplication ---------------------
    Vector2<T> operator*(T scalar)
    {
        return Vector2<T>(x * scalar, y * scalar);
    }

    Vector2<T> &operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;

        return *this;
    }

    Vector2<T> operator*(const Vector2<T> &other)
    {
        return Vector2<T>(x * other.x, y * other.y);
    }

    Vector2<T> &operator*=(const Vector2<T> &other)
    {
        x *= other.x;
        y *= other.y;

        return *this;
    }

    Vector2<T> &operator*=(Vector2<T> &&other)
    {
        x *= other.x;
        y *= other.y;

        return *this;
    }

    // --------------------- division ---------------------
    Vector2<T> operator/(T scalar)
    {
        return Vector2<T>(x / scalar, y / scalar);
    }

    Vector2<T> &operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;

        return *this;
    }

    Vector2<T> operator/(const Vector2<T> &other)
    {
        return Vector2<T>(x / other.x, y * other.y);
    }

    Vector2<T> &operator/=(const Vector2<T> &other)
    {
        x /= other.x;
        y /= other.y;

        return *this;
    }

    Vector2<T> &operator/=(Vector2<T> &&other)
    {
        x /= other.x;
        y /= other.y;

        return *this;
    }

    float lengthSquared()
    {
        return x * x + y * y;
    }

    float length()
    {
        return sqrt(lengthSquared());
    }
};
