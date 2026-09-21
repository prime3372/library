#pragma once

#include <cassert>
#include <utility>
#include <vector>

namespace cp {

template <class T> class weighted_union_find {
 public:
  weighted_union_find() : n(0) {}
  explicit weighted_union_find(int _n)
      : n(_n), par_or_size(_n, -1), diff_weight(_n) {}

  // @return whether diff(a) - diff(b) = d is satisfiable.
  template <class F = void (*)(int, int)>
  bool unite(int a, int b, T d, const F& f = [](int, int) {}) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    d += weight(b) - weight(a);
    a = find(a);
    b = find(b);
    if (a == b) return d == 0;
    if (-par_or_size[a] < -par_or_size[b]) {
      std::swap(a, b);
      d = -d;
    }
    par_or_size[a] += par_or_size[b];
    par_or_size[b] = a;
    diff_weight[b] = -d;
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

  T weight(int a) {
    assert(0 <= a && a < n);
    find(a);
    return diff_weight[a];
  }

  T diff(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    assert(same(a, b));
    return weight(a) - weight(b);
  }

 private:
  int n;
  std::vector<int> par_or_size;
  std::vector<T> diff_weight;

  int _find(int a) {
    if (par_or_size[a] < 0) return a;
    int r = _find(par_or_size[a]);
    diff_weight[a] += diff_weight[par_or_size[a]];
    return par_or_size[a] = r;
  }
};

}  // namespace cp