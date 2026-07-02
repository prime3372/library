#pragma once

#include <algorithm>
#include <concepts>
#include "../ds/hash_map.hpp"
#include "rng.hpp"

template <std::integral T>
std::vector<T> random_choice(T n, int r, bool sorted = false) {
  assert(0 <= n && 0 <= r);
  std::vector<T> res(r);
  hash_map<T> table;
  for (int i = 0; i < r; i++) {
    T j = mt64() % n;
    res[i] = table.count(j) ? j : table[j];
    table[j] = table.count(i) ? i : table[i];
  }
  if (sorted) std::sort(res.begin(), res.end());
  return res;
}
