#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "util/io_utility_base.hpp"

namespace cp {

template <class S, auto op, auto e> class segtree {
 public:
  segtree() : segtree(0) {}
  explicit segtree(int _n) : segtree(_n, e()) {}
  explicit segtree(int _n, const S& val) : segtree(std::vector<S>(_n, val)) {}
  explicit segtree(const std::vector<S>& v) : n(int(v.size())) {
    sz = int(std::bit_ceil((unsigned int)(n)));
    log = std::countr_zero((unsigned int)(sz));
    d = std::vector<S>(2 * sz);
    for (int i = 0; i < n; i++) d[sz + i] = v[i];
    for (int i = sz - 1; i >= 1; i--) update(i);
  }

  void set(int i, const S& x) {
    assert(0 <= i && i < n);
    i += sz;
    d[i] = x;
    for (int j = 1; j <= log; j++) update(i >> j);
  }

  S operator[](int i) const {
    assert(0 <= i && i < n);
    return d[i + sz];
  }

  S prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    S prodl = e(), prodr = e();
    l += sz;
    r += sz;

    while (l < r) {
      if (l & 1) prodl = op(prodl, d[l++]);
      if (r & 1) prodr = op(d[--r], prodr);
      l >>= 1;
      r >>= 1;
    }
    return op(prodl, prodr);
  }

  S all_prod() const { return d[1]; }

  template <class F> int max_right(int l, F f) const {
    assert(0 <= l && l <= n);
    assert(f(e()));
    if (l == n) return n;
    l += sz;
    S product = e();
    do {
      while (l % 2 == 0) l >>= 1;
      if (!f(op(product, d[l]))) {
        while (l < sz) {
          l = 2 * l;
          if (f(op(product, d[l]))) {
            product = op(product, d[l]);
            l++;
          }
        }
        return l - sz;
      }
      product = op(product, d[l]);
      l++;
    } while ((l & -l) != l);
    return n;
  }

  template <class F> int min_left(int r, F f) const {
    assert(0 <= r && r <= n);
    assert(f(e()));
    if (r == 0) return 0;
    r += sz;
    S product = e();
    do {
      r--;
      while (r > 1 && r % 2) r >>= 1;
      if (!f(op(d[r], product))) {
        while (r < sz) {
          r = 2 * r + 1;
          if (f(op(d[r], product))) {
            product = op(d[r], product);
            r--;
          }
        }
        return r + 1 - sz;
      }
      product = op(d[r], product);
    } while ((r & -r) != r);
    return 0;
  }

  int size() const { return n; }

  friend std::ostream& operator<<(std::ostream& os, const segtree& seg) {
    using io_utility::operator<<;
    std::vector<S> v(seg.d.begin() + seg.sz, seg.d.begin() + seg.sz + seg.n);
    return os << v;
  }

 private:
  int n, sz, log;
  std::vector<S> d;

  void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

}  // namespace cp