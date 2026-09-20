#pragma once

#include <algorithm>
#include <cassert>
#include <chrono>
#include <random>
#include <vector>

namespace cp {

class xorshift64 {
 public:
  using result_type = unsigned long long;
  static constexpr unsigned long long min() { return 0; }
  static constexpr unsigned long long max() { return -1ULL; }

  xorshift64() : x(88172645463325252ULL) {}
  explicit xorshift64(unsigned long long seed) : x(seed) {}

  unsigned long long operator()() {
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
  }

 private:
  unsigned long long x;
} rng(std::chrono::duration_cast<std::chrono::nanoseconds>(
          std::chrono::high_resolution_clock::now().time_since_epoch())
          .count());

template <class T> T uniform(T l, T r) {
  assert(l <= r);
  return std::uniform_int_distribution<T>(l, r)(rng);
}

bool uniform_bool() { return rng() % 2; }

double uniform01() {
  static std::uniform_real_distribution dist(0.0, 1.0);
  return dist(rng);
}

template <class Container> void shuffle(Container& a) {
  std::shuffle(a.begin(), a.end(), rng);
}

}  // namespace cp