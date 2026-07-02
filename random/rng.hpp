#pragma once

#include <random>

std::random_device seed_gen;
unsigned int rng_seed = seed_gen();
std::mt19937 mt32(rng_seed);
std::mt19937_64 mt64(rng_seed);
template <class T>
using uniform_real = std::uniform_real_distribution<T>;
