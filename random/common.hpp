#pragma once

#include <cassert>
#include <random>

namespace cp {

std::random_device seed_gen;

std::mt19937 mt32(seed_gen());
std::mt19937_64 mt64(seed_gen());

template <class T> T uniform(T l, T r) {
  assert(l <= r);
  return T(mt64() % (unsigned long long)(r - l + 1) + l);
}

bool unifom_bool() { return uniform(0, 1) == 1; }

} // namespace cp