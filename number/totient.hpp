#pragma once

#include <cassert>

#include "number/factorize.hpp"

namespace cp {

long long totient(long long n) {
  assert(1 <= n);
  auto f = factorize(n);
  for (auto& [p, e] : f) {
    n /= p;
    n *= (p - 1);
  }
  return n;
}

}  // namespace cp