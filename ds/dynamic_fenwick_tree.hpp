#pragma once

#include <cassert>
#include <iostream>

#include "ds/hash_map.hpp"

namespace cp {

template <class T> class dynamic_fenwick_tree {
  using ull = unsigned long long;

 public:
  dynamic_fenwick_tree() : n(0) {}
  explicit dynamic_fenwick_tree(ull _n) : n(_n) {}

  void add(ull i, T x) {
    assert(i < n);
    i++;
    while (i <= n) {
      d[i - 1] += x;
      i += i & -i;
    }
  }

  void set(ull i, T x) {
    assert(i < n);
    add(i, x - (*this)[i]);
  }

  T operator[](ull i) const {
    assert(i < n);
    return sum(i + 1) - sum(i);
  }

  T sum(ull l, ull r) const {
    assert(l <= r && r <= n);
    return sum(r) - sum(l);
  }

  T sum(ull r) const {
    assert(r <= n);
    T s = 0;
    while (r) {
      s += d.get(r - 1);
      r -= r & -r;
    }
    return s;
  }

  void dual_add(ull l, ull r, T x) {
    assert(l <= r && r <= n);
    if (l < n) add(l, x);
    if (r < n) add(r, -x);
  }

  T dual_get(ull i) const {
    assert(i < n);
    return sum(i + 1);
  }

  ull lower_bound(T w) const {
    if (w <= 0) return 0;
    ull lb = 0, k = 1;
    while ((k << 1) <= n) k <<= 1;
    while (k) {
      if (lb + k <= n && d.get(lb + k - 1) < w) {
        w -= d.get(lb + k - 1);
        lb += k;
      }
      k >>= 1;
    }
    return lb;
  }

  ull upper_bound(T w) const {
    if (w < 0) return 0;
    ull ub = 0, k = 1;
    while ((k << 1) <= n) k <<= 1;
    while (k) {
      if (ub + k <= n && d.get(ub + k - 1) <= w) {
        w -= d.get(ub + k - 1);
        ub += k;
      }
      k >>= 1;
    }
    return ub;
  }

  ull size() const { return n; }

  friend std::ostream& operator<<(std::ostream& os,
                                  const dynamic_fenwick_tree& fw) {
    for (ull i = 0; i < fw.n; i++) {
      os << fw[i];
      if (i != fw.n - 1) os << " ";
    }
    return os;
  }

 private:
  ull n;
  hash_map<ull, T> d;
};

}  // namespace cp