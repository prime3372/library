#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <type_traits>
#include <vector>

#include "random/engine.hpp"

namespace cp {

std::vector<int> random_perm(int n) {
  assert(0 <= n);
  std::vector<int> p(n);
  std::iota(p.begin(), p.end(), 0);
  shuffle(p);
  return p;
}

std::vector<int> random_comb(int n, int r) {
  assert(0 <= r && r <= n);
  auto p = random_perm(n);
  std::sort(p.begin(), p.begin() + r);
  p.erase(p.begin() + r, p.end());
  return p;
}

}  // namespace cp