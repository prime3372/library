#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace cp {

class enumerate_union_find {
 public:
  enumerate_union_find() : n(0) {}
  explicit enumerate_union_find(int _n) : n(_n), par_or_size(_n, -1), nxt(_n) {
    for (int i = 0; i < n; i++) nxt[i] = i;
  }

  template <class F = void (*)(int, int)>
  bool unite(int a, int b, const F& f = [](int, int) {}) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (-par_or_size[a] < -par_or_size[b]) std::swap(a, b);
    par_or_size[a] += par_or_size[b];
    par_or_size[b] = a;
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
    return -par_or_size[find(a)];
  }

  int size() const { return n; }

  // @return the list of vertices contained in the connected component to which
  // vertex a belongs
  // @note The order of vertices in the return value is undefined.
  std::vector<int> enumerate(int a) const {
    assert(0 <= a && a < n);
    std::vector<int> res = {a};
    for (int i = nxt[a]; i != a; i = nxt[i]) {
      res.push_back(i);
    }
    return res;
  }

 private:
  int n;
  std::vector<int> par_or_size, nxt;
  int _find(int a) {
    if (par_or_size[a] < 0) return a;
    return par_or_size[a] = _find(par_or_size[a]);
  }
};

}  // namespace cp