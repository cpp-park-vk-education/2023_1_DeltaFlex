#pragma once

#include <array>
#include <iostream>

template <typename T, size_t N, size_t M, size_t L>
std::array<std::array<T, L>, N> matrixMultiplication(
    std::array<std::array<T, M>, N> &a,
    std::array<std::array<T, L>, M> &b);

template <typename T, size_t M, size_t L>
std::array<T, L> matrixMultiplication(
    std::array<T, M> &a,
    std::array<std::array<T, L>, M> &b);

template <typename T, size_t N, size_t M>
std::array<T, N> matrixMultiplication(
    std::array<std::array<T, M>, N> &a,
    std::array<T, M> &b);

template <typename T, size_t N, size_t M>
std::array<std::array<T, M>, N> activeFunc(
    std::array<std::array<T, M>, N> &matrix);

template <typename T, size_t N>
std::array<T, N> activeFunc(
    std::array<T, N> &matrix);

template <typename T, size_t N, size_t M>
std::array<std::array<T, M>, N> matrixAddition(
    std::array<std::array<T, M>, N> &a,
    std::array<std::array<T, M>, N> &b);

template <typename T, size_t N>
std::array<T, N> matrixAddition(
    std::array<T, N> &a,
    std::array<T, N> &b);