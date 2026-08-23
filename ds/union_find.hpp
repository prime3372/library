#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace cp {

class union_find {
 public:
  union_find() : n(0) {}
  explicit union_find(int _n) : n(_n), data(_n, -1) {}

  bool unite(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (-data[a] < -data[b]) std::swap(a, b);
    data[a] += data[b];
    data[b] = a;
    return true;
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
    return -data[find(a)];
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
    res.erase(
        std::remove_if(res.begin(), res.end(),
                       [&](const std::vector<int>& v) { return v.empty(); }),
        res.end());
    return res;
  }

 private:
  int n;
  std::vector<int> data;
  int _find(int a) {
    if (data[a] < 0) return a;
    return data[a] = _find(data[a]);
  }
};

}  // namespace cp