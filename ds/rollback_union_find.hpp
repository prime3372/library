#pragma once

#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

namespace cp {

class rollback_union_find {
 public:
  rollback_union_find() : n(0) {}
  explicit rollback_union_find(int _n) : n(_n), par_or_size(_n, -1) {}

  template <class F = void (*)(int, int)>
  bool unite(int a, int b, const F& f = [](int, int) {}) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = find(a);
    b = find(b);
    history.emplace_back(a, b, par_or_size[a], par_or_size[b]);
    if (a == b) return false;
    if (-par_or_size[a] < -par_or_size[b]) std::swap(a, b);
    par_or_size[a] += par_or_size[b];
    par_or_size[b] = a;
    f(a, b);
    return true;
  }

  int find(int a) {
    assert(0 <= a && a < n);
    while (par_or_size[a] >= 0) a = par_or_size[a];
    return a;
  }

  bool same(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    return find(a) == find(b);
  }

  int size(int a) {
    assert(0 <= a && a < n);
    return -par_or_size[find(a)];
  }

  int size() const { return n; }

  std::vector<std::vector<int>> groups() {
    std::vector<int> root(n);
    for (int i = 0; i < n; i++) {
      root[i] = find(i);
    }
    std::vector<std::vector<int>> res(n);
    for (int i = 0; i < n; i++) {
      res[root[i]].push_back(i);
    }
    res.erase(
        std::remove_if(res.begin(), res.end(),
                       [&](const std::vector<int>& v) { return v.empty(); }),
        res.end());
    return res;
  }

  void undo() {
    auto [a, b, x, y] = history.back();
    history.pop_back();
    par_or_size[a] = x;
    par_or_size[b] = y;
  }

  void snapshot() { inner_snap = int(history.size()); }
  void rollback() {
    assert(inner_snap != -1);
    while (inner_snap < int(history.size())) undo();
  }

 private:
  int n, inner_snap = -1;
  std::vector<int> par_or_size;
  std::vector<std::tuple<int, int, int, int>> history;
};

}  // namespace cp