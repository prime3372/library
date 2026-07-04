#pragma once

#include <algorithm>
#include <cassert>
#include <concepts>
#include <numeric>
#include <vector>

#include "rng.hpp"

namespace cp {

template <std::integral T> std::vector<T> random_seq(int n, T l, T r, bool sorted = false) {
  assert(0 <= n && (n == 0 || l < r));
  std::vector<T> seq(n);
  for (int i = 0; i < n; i++) {
    seq[i] = mt64() % (r - l) + l;
  }
  if (sorted) std::sort(seq.begin(), seq.end());
  return seq;
}

template <std::floating_point T> std::vector<T> random_seq(int n, T l, T r, bool sorted = false) {
  assert(0 <= n && (n == 0 || l < r));
  std::vector<T> seq(n);
  for (int i = 0; i < n; i++) {
    seq[i] = uniform_real<T>(l, r)(mt32);
  }
  if (sorted) std::sort(seq.begin(), seq.end());
  return seq;
}

std::vector<int> random_perm(int n) {
  std::vector<int> p(n);
  std::iota(p.begin(), p.end(), 0);
  std::shuffle(p.begin(), p.end(), mt32);
  return p;
}

} // namespace cp