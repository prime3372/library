#pragma once

#include <cassert>
#include <cstddef>
#include "hash_map.hpp"

template <class T> struct dynamic_fenwick_tree {
public:
  dynamic_fenwick_tree() : n(0) {}
  explicit dynamic_fenwick_tree(size_t _n) : n(_n) {}

  void add(size_t i, T x) {
    assert(i < n);
    i++;
    while (i <= n) {
      d[i - 1] += x;
      i += i & (~i + 1);
    }
  }

  T operator[](size_t i) const {
    assert(i < n);
    return sum(i + 1) - sum(i);
  }

  T sum(size_t l, size_t r) const {
    assert(l <= r && r <= n);
    return sum(r) - sum(l);
  }

  T sum(size_t r) const {
    assert(r <= n);
    T s = 0;
    while (r) {
      s += d[r - 1];
      r -= r & (~r + 1);
    }
    return s;
  }

  void imos_add(size_t l, size_t r, T x) {
    assert(l <= r && r <= n);
    if (l < n) add(l, x);
    if (r < n) add(r, -x);
  }

  T imos_get(size_t i) const {
    assert(i < n);
    return sum(i + 1);
  }

  size_t lower_bound(T w) const {
    if (w <= 0) return 0;
    size_t lb = 0, k = 1;
    while ((k << 1) <= n) k <<= 1;
    while (k) {
      if (lb + k <= n && d[lb + k - 1] < w) {
        w -= d[lb + k - 1];
        lb += k;
      }
      k >>= 1;
    }
    return lb;
  }

  size_t upper_bound(T w) const {
    if (w < 0) return 0;
    size_t ub = 0, k = 1;
    while ((k << 1) <= n) k <<= 1;
    while (k) {
      if (ub + k <= n && d[ub + k - 1] <= w) {
        w -= d[ub + k - 1];
        ub += k;
      }
      k >>= 1;
    }
    return ub;
  }

  size_t size() const { return n; }

private:
  size_t n;
  hash_map<size_t, T> d;
};
