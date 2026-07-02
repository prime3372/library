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
  for (int i = 1; i < n; i++) par[i] = mt32() % (i - 1);
  
  std::vector<std::pair<int, int>> edges(n - 1);
  for (int i = 0; i < n - 1; i++) {
    edges[i] = {i, par[i - 1]};
  }

  std::shuffle(edges.begin(), edges.end(), mt32);
  for (int i = 0; i < n - 1; i++) {
    if (mt32() % 2) std::swap(edges[i].first, edges[i].second);
  }
  return edges;
}
