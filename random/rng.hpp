#pragma once

#include <random>

std::random_device seed_gen;
std::mt19937 mt32(seed_gen());
std::mt19937_64 mt64(seed_gen());
template <class T>
using uniform_real = std::uniform_real_distribution<T>;
