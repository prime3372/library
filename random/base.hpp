#pragma once

#include <cassert>
#include <chrono>
#include <random>

namespace cp {

namespace internal {

unsigned int rand_time = (unsigned int)(std::chrono::duration_cast<std::chrono::nanoseconds>(
                                        std::chrono::high_resolution_clock::now().time_since_epoch())
                                        .count());

} // namespace internal

std::mt19937 mt32(internal::rand_time);
std::mt19937_64 mt64(internal::rand_time);

template <class T> T uniform(T l, T r) {
  assert(l <= r);
  return T(mt64() % (unsigned long long)(r - l + 1) + l);
}

bool unifom_bool() { return uniform(0, 1) == 1; }

template <class T> T uniform_real(T l, T r) {
  assert(l <= r);
  return std::uniform_real_distribution<T>(l, r)(mt32);
}

} // namespace cp