#pragma once

#include <functional>
#include <queue>
#include <utility>
#include <vector>
#include "rng.hpp"

std::vector<std::pair<int, int>> random_tree(int n) {
  assert(1 <= n);
  if (n == 1) return {};

  // build a tree based on a prufer code
  std::vector<std::pair<int, int>> tree(n - 1);
  std::vector<int> prufer = rng<int>::seq(n - 2, 0, n);
  std::vector<int> bucket(n);
  for (int i = 0; i < n - 2; i++) {
    bucket[prufer[i]]++;
  }
  std::priority_queue<int> q;
  for (int i = 0; i < n; i++) {
    if (bucket[i] == 0) q.push(i);
  }
  for (int i = 0; i < n - 2; i++) {
    int a = prufer.back();
    int b = q.top();
    prufer.pop_back();
    q.pop();
    tree[i] = {a, b};
    bucket[a]--;
    if (bucket[a] == 0) q.push(a);   
  }
  int tmp = q.top();
  q.pop();
  tree.back() = {tmp, q.top()};

  // shuffle the order
  std::shuffle(tree.begin(), tree.end(), internal::mt);
  for (int i = 0; i < n - 1; i++) {
    if (rng<int>::rand(0, 2)) std::swap(tree[i].first, tree[i].second);
  }
  return tree;
}
