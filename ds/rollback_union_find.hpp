#pragma once

#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

namespace cp {

class rollback_union_find {
 public:
  rollback_union_find() : n(0), cnt(0), inner_snap(0) {}
  explicit rollback_union_find(int _n)
      : n(_n), cnt(_n), inner_snap(0), par_size(_n, -1) {}

  bool unite(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = find(a);
    b = find(b);
    history.emplace_back(a, b, par_size[a], par_size[b]);
    if (a == b) return false;
    if (-par_size[a] < -par_size[b]) std::swap(a, b);
    par_size[a] += par_size[b];
    par_size[b] = a;
    cnt--;
    return true;
  }

  int find(int a) {
    assert(0 <= a && a < n);
    while (par_size[a] >= 0) a = par_size[a];
    return a;
  }

  bool same(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    return find(a) == find(b);
  }

  int size(int a) {
    assert(0 <= a && a < n);
    return -par_size[find(a)];
  }

  int size() const { return n; }

  int count() const { return cnt; }

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
    par_size[a] = x;
    par_size[b] = y;
    if (a != b) cnt++;
  }

  void snapshot() { inner_snap = int(history.size()); }
  void rollback() {
    while (inner_snap < int(history.size())) undo();
  }

 private:
  int n, cnt, inner_snap;
  std::vector<int> par_size;
  std::vector<std::tuple<int, int, int, int>> history;
};

}  // namespace cp