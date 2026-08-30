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

template <class S, auto op, auto e, class F, auto act, auto compose, auto id>
class lazy_segtree {
 public:
  lazy_segtree() : lazy_segtree(0) {}
  explicit lazy_segtree(int _n) : lazy_segtree(_n, e()) {}
  explicit lazy_segtree(int _n, const S& val)
      : lazy_segtree(std::vector<S>(_n, val)) {}
  explicit lazy_segtree(const std::vector<S>& v) : n(int(v.size())) {
    sz = int(std::bit_ceil((unsigned int)(n)));
    log = std::countr_zero((unsigned int)(sz));
    d = std::vector<S>(2 * sz);
    lz = std::vector<F>(sz, id());
    for (int i = 0; i < n; i++) d[sz + i] = v[i];
    for (int i = sz - 1; i >= 1; i--) update(i);
  }

  void set(int i, const S& x) {
    assert(0 <= i && i < n);
    i += sz;
    for (int j = log; j >= 1; j--) push(i >> j);
    d[i] = x;
    for (int j = 1; j <= log; j++) update(i >> j);
  }

  S operator[](int i) {
    assert(0 <= i && i < n);
    i += sz;
    for (int j = log; j >= 1; j--) push(i >> j);
    return d[i];
  }

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    if (l == r) return e();

    l += sz;
    r += sz;

    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }

    S prodl = e(), prodr = e();
    while (l < r) {
      if (l & 1) prodl = op(prodl, d[l++]);
      if (r & 1) prodr = op(d[--r], prodr);
      l >>= 1;
      r >>= 1;
    }

    return op(prodl, prodr);
  }

  S all_prod() const { return d[1]; }

  void apply(int i, F f) {
    assert(0 <= i && i < n);
    i += sz;
    for (int j = log; j >= 1; j--) push(i >> j);
    d[i] = act(f, d[i]);
    for (int j = 1; j <= log; j++) update(i >> j);
  }

  void apply(int l, int r, const F& f) {
    assert(0 <= l && l <= r && r <= n);
    if (l == r) return;

    l += sz;
    r += sz;

    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }

    {
      int l2 = l, r2 = r;
      while (l < r) {
        if (l & 1) all_apply(l++, f);
        if (r & 1) all_apply(--r, f);
        l >>= 1;
        r >>= 1;
      }
      l = l2;
      r = r2;
    }

    for (int i = 1; i <= log; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }

  template <class G> int max_right(int l, G g) {
    assert(0 <= l && l <= n);
    assert(g(e()));
    if (l == n) return n;
    l += sz;
    for (int i = log; i >= 1; i--) push(l >> i);
    S product = e();
    do {
      while (l % 2 == 0) l >>= 1;
      if (!g(op(product, d[l]))) {
        while (l < sz) {
          push(l);
          l = 2 * l;
          if (g(op(product, d[l]))) {
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

  template <class G> int min_left(int r, G g) {
    assert(0 <= r && r <= n);
    assert(g(e()));
    if (r == 0) return 0;
    r += sz;
    for (int i = log; i >= 1; i--) push((r - 1) >> i);
    S product = e();
    do {
      r--;
      while (r > 1 && r % 2) r >>= 1;
      if (!g(op(d[r], product))) {
        while (r < sz) {
          push(r);
          r = 2 * r + 1;
          if (g(op(d[r], product))) {
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

  friend std::ostream& operator<<(std::ostream& os, lazy_segtree seg) {
    std::vector<std::string> outs(seg.n);
    std::ostringstream oss;
    for (int i = 0; i < int(outs.size()); i++) {
      oss << seg[i];
      outs[i] = oss.str();
      oss.str("");
    }
    return os << internal::combine_outputs(outs);
  }

 private:
  int n, sz, log;
  std::vector<S> d;
  std::vector<F> lz;

  void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
  void all_apply(int k, F f) {
    d[k] = act(f, d[k]);
    if (k < sz) lz[k] = compose(f, lz[k]);
  }
  void push(int k) {
    all_apply(2 * k, lz[k]);
    all_apply(2 * k + 1, lz[k]);
    lz[k] = id();
  }
};

}  // namespace cp