#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace cp {

template <class T> struct union_find_with_potential {
public:
  union_find_with_potential() : n(0) {}
  explicit union_find_with_potential(int _n) : n(_n), parent_or_size(_n, -1), diff_weight(_n) {}

  bool unite(int a, int b, T d) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    d += weight(b) - weight(a);
    a = find(a);
    b = find(b);
    if (a == b) return d == 0;
    if (-parent_or_size[a] > -parent_or_size[b]) {
      std::swap(a, b);
      d = -d;
    }
    parent_or_size[b] += parent_or_size[a];
    parent_or_size[a] = b;
    diff_weight[a] = d;
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
    return -parent_or_size[find(a)];
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
    return weight(a) - weight(b);
  }

private:
  int n;
  std::vector<int> parent_or_size;
  std::vector<T> diff_weight;
  int _find(int a) {
    if (parent_or_size[a] < 0) return a;
    int r = _find(parent_or_size[a]);
    diff_weight[a] += diff_weight[parent_or_size[a]];
    return parent_or_size[a] = r;
  }
};

} // namespace cp