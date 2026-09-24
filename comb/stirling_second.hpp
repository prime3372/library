#pragma once

#include <cassert>
#include <vector>

#include "comb/binom_mod.hpp"
#include "poly/convolution.hpp"

namespace cp {

// https://en.wikipedia.org/wiki/Stirling_numbers_of_the_second_kind#Explicit_formula
template <class mint> std::vector<mint> stirling_second(int n) {
  assert(0 <= n);
  binom_mod<mint> binom(n);
  std::vector<mint> a(n + 1), b(n + 1);
  for (int i = 0; i <= n; i++) a[i] = (i % 2 ? -1 : 1) * binom.ifact(i);
  for (int i = 0; i <= n; i++) b[i] = mint(i).pow(n) * binom.ifact(i);
  auto c = convolution(a, b);
  c.resize(n + 1);
  return c;
}

}  // namespace cp