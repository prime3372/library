#pragma once

#include <cassert>
#include <vector>

template <class T> struct fenwick_tree {
public:
  fenwick_tree() : n(0) {}
  explicit fenwick_tree(int _n) : n(_n), d(_n) {}

  void add(int i, T x) {
    assert(0 <= i && i < n);
    i++;
    while (i <= n) {
      d[i - 1] += x;
      i += i & -i;
    }
  }

  T operator[](int i) const {
    assert(0 <= i && i < n);
    return sum(i + 1) - sum(i);
  }

  T sum(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return sum(r) - sum(l);
  }

  T sum(int r) const {
    assert(0 <= r && r <= n);
    T s = 0;
    while (r) {
      s += d[r - 1];
      r -= r & -r;
    }
    return s;
  }

  void imos_add(int l, int r, T x) {
    assert(0 <= l && l <= r && r <= n);
    if (l < n) add(l, x);
    if (r < n) add(r, -x);
  }

  T imos_get(int i) const {
    assert(0 <= i && i < n);
    return sum(i + 1);
  }

  int lower_bound(T w) const {
    if (w <= 0) return 0;
    int lb = 0, k = 1;
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

  int upper_bound(T w) const {
    if (w < 0) return 0;
    int ub = 0, k = 1;
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

  int size() const { return n; }

private:
  int n;
  std::vector<T> d;
};
