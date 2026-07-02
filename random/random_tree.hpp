#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include "rng.hpp"

std::vector<std::pair<int, int>> random_tree(int n) {
  assert(1 <= n);
  if (n == 1) return {};

  std::vector<int> par(n, -1);
  for (int i = 1; i < n; i++) par[i] = mt32() % i;
  
  std::vector<std::pair<int, int>> edges(n - 1);
  for (int i = 1; i < n; i++) {
    edges[i - 1] = {i, par[i]};
  }

  std::shuffle(edges.begin(), edges.end(), mt32);
  for (auto& e : edges) {
    if (mt32() % 2) std::swap(e.first, e.second);
  }
  return edges;
}
