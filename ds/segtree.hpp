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
  explicit segtree(int _n, const S& val = e())
      : segtree(std::vector<S>(_n, val)) {}
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
    S sml = e(), smr = e();
    l += sz;
    r += sz;

    while (l < r) {
      if (l & 1) sml = op(sml, d[l++]);
      if (r & 1) smr = op(d[--r], smr);
      l >>= 1;
      r >>= 1;
    }
    return op(sml, smr);
  }

  S all_prod() const { return d[1]; }

  template <class F> int max_right(int l, F f) const {
    assert(0 <= l && l <= n);
    assert(f(e()));
    if (l == n) return n;
    l += sz;
    S sm = e();
    do {
      while (l % 2 == 0) l >>= 1;
      if (!f(op(sm, d[l]))) {
        while (l < sz) {
          l = 2 * l;
          if (f(op(sm, d[l]))) {
            sm = op(sm, d[l]);
            l++;
          }
        }
        return l - sz;
      }
      sm = op(sm, d[l]);
      l++;
    } while ((l & -l) != l);
    return n;
  }

  template <class F> int min_left(int r, F f) const {
    assert(0 <= r && r <= n);
    assert(f(e()));
    if (r == 0) return 0;
    r += sz;
    S sm = e();
    do {
      r--;
      while (r > 1 && r % 2) r >>= 1;
      if (!f(op(d[r], sm))) {
        while (r < sz) {
          r = 2 * r + 1;
          if (f(op(d[r], sm))) {
            sm = op(d[r], sm);
            r--;
          }
        }
        return r + 1 - sz;
      }
      sm = op(d[r], sm);
    } while ((r & -r) != r);
    return 0;
  }

  int size() const { return n; }

  friend std::ostream& operator<<(std::ostream& os, const segtree& seg) {
    using io_utility::operator<<;
    return os << std::vector<S>(seg.d.begin() + seg.sz,
                                seg.d.begin() + seg.sz + seg.n);
  }

 private:
  int n, sz, log;
  std::vector<S> d;

  void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

}  // namespace cp