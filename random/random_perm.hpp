#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <type_traits>
#include <vector>

#include "random/base.hpp"

namespace cp {

std::vector<int> random_perm(int n) {
  assert(0 <= n);
  std::vector<int> p(n);
  std::iota(p.begin(), p.end(), 0);
  std::shuffle(p.begin(), p.end(), mt32);
  return p;
}

}  // namespace cp