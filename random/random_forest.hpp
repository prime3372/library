#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include "rng.hpp"

std::vector<std::pair<int, int>> random_forest(int n) {
  assert(1 <= n);
  if (n == 1) return {};

  std::vector<int> par(n);
  for (int i = 0; i < n; i++) par[i] = mt32() % (i + 1);
  
  std::vector<std::pair<int, int>> edges(n - 1);
  for (int i = 0; i < n; i++) {
    if (par[i] != i) edges[i] = {i, par[i]};
  }

  std::shuffle(edges.begin(), edges.end(), mt32);
  for (auto& e : edges) {
    if (mt32() % 2) std::swap(e.first, e.second);
  }
  return edges;
}
