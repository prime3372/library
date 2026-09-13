#pragma once

#include <cassert>

#include "number/factorize.hpp"

namespace cp {

long long totient(long long n) {
  assert(1 <= n);
  for (auto [p, e] : factorize(n)) {
    n /= p;
    n *= (p - 1);
  }
  return n;
}

}  // namespace cp