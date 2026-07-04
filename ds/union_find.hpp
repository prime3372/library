#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace cp {

struct union_find {
public:
  union_find() : n(0) {}
  explicit union_find(int _n) : n(_n), parent_or_size(_n, -1) {}

  int unite(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = find(a);
    b = find(b);
    if (a == b) return a;
    if (-parent_or_size[a] < -parent_or_size[b]) std::swap(a, b);
    parent_or_size[a] += parent_or_size[b];
    parent_or_size[b] = a;
    return a;
  }

  int find(int a) {
    assert(0 <= a && a < n);
    return _find(a);
  }

  bool same(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    return find(a) == find(b);
  }

  int size(int a) {
    assert(0 <= a && a < n);
    return -parent_or_size[find(a)];
  }

  int size() const { return n; }

  std::vector<std::vector<int>> groups() {
    std::vector<int> root(n), group_size(n);
    for (int i = 0; i < n; i++) {
      root[i] = find(i);
      group_size[root[i]]++;
    }
    std::vector<std::vector<int>> res(n);
    for (int i = 0; i < n; i++) {
      res[i].reserve(group_size[i]);
    }
    for (int i = 0; i < n; i++) {
      res[root[i]].push_back(i);
    }
    res.erase(std::remove_if(res.begin(), res.end(),
                             [&](const std::vector<int>& v) { return v.empty(); }),
              res.end());
    return res;
  }

private:
  int n;
  std::vector<int> parent_or_size;
  int _find(int a) {
    if (parent_or_size[a] < 0) return a;
    return parent_or_size[a] = _find(parent_or_size[a]);
  }
};

} // namespace cp