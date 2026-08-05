#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "random/get_rand.hpp"

namespace cp {

std::vector<std::pair<int, int>> random_tree(int n, int root = 0) {
  assert(1 <= n);
  assert(0 <= root && root < n);
  if (n == 1) return {};

  std::vector<int> par(n, -1);
  for (int i = root + 1; i < n; i++) {
    par[i] = get_rand(root, i);;
  }
  for (int i = 0; i < root; i++) {
    par[i] = get_rand(root, n + i) % n;
  }

  std::vector<std::pair<int, int>> edges;
  edges.reserve(n - 1);
  for (int i = 0; i < n; i++) {
    if (par[i] == -1) continue;
    edges.emplace_back(par[i], i);
  }
  std::shuffle(edges.begin(), edges.end(), mt32);

  return edges;
}

std::vector<std::pair<int, int>> random_forest(int n) {
  assert(1 <= n);
  if (n == 1) return {};

  std::vector<int> par(n);
  for (int i = 0; i < n; i++) par[i] = get_rand(i + 1);

  std::vector<std::pair<int, int>> edges;
  for (int i = 0; i < n; i++) {
    if (par[i] != i) edges.emplace_back(par[i], i);
  }

  std::shuffle(edges.begin(), edges.end(), mt32);
  return edges;
}

} // namespace cp