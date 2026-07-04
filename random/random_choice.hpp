#pragma once

#include <algorithm>
#include <concepts>

#include "ds/hash_map.hpp"
#include "util/hash_combine.hpp"
#include "rng.hpp"

namespace cp {

template <bool sorted = false>
std::vector<size_t> random_choice(size_t n, int r) {
  assert(0 <= r);
  std::vector<size_t> res(r);
  hash_map<size_t, size_t> table;
  for (int i = 0; i < r; i++) {
    size_t j = mt64() % n;
    res[i] = table.count(j) ? j : table[j];
    table[j] = table.count(i) ? i : table[i];
  }
  if constexpr (sorted) std::sort(res.begin(), res.end());
  return res;
}

} // namespace cp