#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "ds/persistent-array.hpp"

namespace cp {

struct PersistentUnionFind {
 public:
  using NodePtr = typename PersistentArray<int>::NodePtr;

  PersistentUnionFind() : n(0) {}
  explicit PersistentUnionFind(int _n) : n(_n), par_or_size(_n, -1) {}

  template <class F = void (*)(int, int)>
  bool unite(int a, int b, const F& f = [](int, int) {}) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (-par_or_size[a] < -par_or_size[b]) std::swap(a, b);
    par_or_size.set(a, par_or_size[a] + par_or_size[b]);
    par_or_size.set(b, a);
    f(a, b);
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
    return -par_or_size[find(a)];
  }

  int size() const { return n; }

  NodePtr snapshot() { return par_or_size.snapshot(); }
  void restore(NodePtr p) { par_or_size.restore(p); }

 private:
  int n;
  PersistentArray<int> par_or_size;
  int _find(int a) {
    if (par_or_size[a] < 0) return a;
    int res = _find(par_or_size[a]);
    par_or_size.set(a, res);
    return res;
  }
};

}  // namespace cp