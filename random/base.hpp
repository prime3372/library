#pragma once

#include <cassert>
#include <chrono>
#include <random>
#include <vector>

namespace cp {

namespace internal {

const unsigned int rand_time =
    (unsigned int)(std::chrono::duration_cast<std::chrono::nanoseconds>(
                       std::chrono::high_resolution_clock::now()
                           .time_since_epoch())
                       .count());

}  // namespace internal

std::mt19937 mt32(internal::rand_time);
std::mt19937_64 mt64(internal::rand_time);

template <class T> T uniform(T l, T r) {
  assert(l <= r);
  return std::uniform_int_distribution<T>(l, r)(mt32);
}

bool uniform_bool() { return uniform(0, 1) == 1; }

// random choice 2 disjoint elements from [l, r]
template <class T> std::pair<T, T> uniform_pair(T l, T r) {
  assert(l < r);
  T a = uniform(0, r - 1);
  T b = uniform(a + 1, r);
  return {a, b};
}

}  // namespace cp