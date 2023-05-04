#include "MatrixActions.hpp"

template <typename T, size_t N, size_t M, size_t L>
std::array<std::array<T, L>, N> matrixMultiplication(
    std::array<std::array<T, M>, N> &a,
    std::array<std::array<T, L>, M> &b)
{
    std::array<std::array<T, L>, N> result{};
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < L; ++j)
        {
            for (size_t k = 0; k < M; ++k)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

template <typename T, size_t M, size_t L>
std::array<T, L> matrixMultiplication(
    std::array<T, M> &a,
    std::array<std::array<T, L>, M> &b)
{
    std::array<T, L> result{};
    for (size_t j = 0; j < L; ++j)
    {
        for (size_t k = 0; k < M; ++k)
        {
            result[j] += a[k] * b[k][j];
        }
    }
    return result;
}

template <typename T, size_t N, size_t M>
std::array<T, N> matrixMultiplication(
    std::array<std::array<T, M>, N> &a,
    std::array<T, M> &b)
{
    std::array<T, N> result{};
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t k = 0; k < M; ++k)
        {
            result[i] += a[i][k] * b[k];
        }
    }
    return result;
}

template <typename T, size_t N, size_t M>
std::array<std::array<T, M>, N> activeFunc(
    std::array<std::array<T, M>, N> &matrix)
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            matrix[i][j] = tanh(matrix[i][j]);
        }
    }
}

template <typename T, size_t N>
std::array<T, N> activeFunc(
    std::array<T, N> &matrix)
{
    std::array<T, N> result{};
    for (size_t i = 0; i < N; i++)
    {
        result[i] = tanh(matrix[i]);
    }
    return result;
}

template <typename T, size_t N, size_t M>
std::array<std::array<T, M>, N> matrixAddition(
    std::array<std::array<T, M>, N> &a,
    std::array<std::array<T, M>, N> &b)
{
    std::array<std::array<T, M>, N> result{};
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < M; ++j)
        {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    return result;
}

template <typename T, size_t N>
std::array<T, N> matrixAddition(
    std::array<T, N> &a,
    std::array<T, N> &b)
{
    std::array<T, N> result{};
    for (size_t i = 0; i < N; ++i)
    {
        result[i] = a[i] + b[i];
    }
    return result;
}
