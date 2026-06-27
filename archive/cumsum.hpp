#pragma once

#include <cassert>
#include <vector>

template <class T> struct cumsum {
public:
  cumsum() : n(0) {}
  cumsum(int _n) : n(_n), a(_n) {}
  cumsum(int _n, T x) : n(_n), a(_n, x) {}

  void accumulate() {
    cum.resize(n + 1);
    for (int i = 0; i < n; i++) {
      cum[i + 1] = cum[i] + a[i];
    }
    accumulated = true;
  }

  T& operator[](int i) {
    assert(0 <= i && i < n);
    return a[i];
  }
  T operator[](int i) const {
    assert(0 <= i && i < n);
    return a[i];
  }

  T sum(int r) {
    assert(0 <= r && r <= n);
    if (!accumulated) accumulate();
    return cum[r];
  }

  T sum(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    if (!accumulated) accumulate();
    return cum[r] - cum[l];
  }

  void imos(int l, int r, T x) {
    assert(0 <= l && l <= r && r <= n);
    if (l < n) a[l] += x;
    if (r < n) a[r] -= x;
  }

  int size() const { return n; }

private:
  int n;
  bool accumulated = false;
  std::vector<T> a, cum;
};
