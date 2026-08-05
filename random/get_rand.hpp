#pragma once

#include <cassert>
#include <random>
#include <type_traits>

#include "util/type_traits.hpp"

namespace cp {

std::random_device seed_gen;

std::mt19937 mt32(seed_gen());
std::mt19937_64 mt64(seed_gen());

template <class T> requires internal::is_integral_v<T>
T get_rand(T n) {
  assert(1 <= n);
  return T(mt64() % n);
}

template <class T> requires internal::is_integral_v<T>
T get_rand(T l, T r) {
  assert(l < r);
  return T(mt64() % (r - l) + l);
}

} // namespace cp