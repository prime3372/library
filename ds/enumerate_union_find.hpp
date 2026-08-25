#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace cp {

class enumerate_union_find {
 public:
  enumerate_union_find() : n(0), cnt(0) {}
  explicit enumerate_union_find(int _n)
      : n(_n), cnt(_n), par_size(_n, -1), nxt(_n) {
    for (int i = 0; i < n; i++) nxt[i] = i;
  }

  bool unite(int a, int b) {
    return unite(a, b, [](int, int) {});
  }
  template <class F> bool unite(int a, int b, F f) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (-par_size[a] < -par_size[b]) std::swap(a, b);
    par_size[a] += par_size[b];
    par_size[b] = a;
    cnt--;
    f(a, b);
    std::swap(nxt[a], nxt[b]);
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
    return -par_size[find(a)];
  }

  int size() const { return n; }

  int count() const { return cnt; }

  // @note The order of the vertices is undefined.
  std::vector<int> enumerate(int a) const {
    assert(0 <= a && a < n);
    std::vector<int> res = {a};
    for (int i = nxt[a]; i != a; i = nxt[i]) {
      res.push_back(i);
    }
    return res;
  }

 private:
  int n, cnt;
  std::vector<int> par_size, nxt;
  int _find(int a) {
    if (par_size[a] < 0) return a;
    return par_size[a] = _find(par_size[a]);
  }
};

}  // namespace cp