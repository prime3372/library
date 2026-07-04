#pragma once

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <vector>

#include "../algebra/acted_monoid.hpp"

namespace cp {

template <acted_monoid M> struct lazy_segtree {
  using S = typename M::S;
  using F = typename M::F;

public:
  lazy_segtree() : lazy_segtree(0) {}
  explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, M::e())) {}
  explicit lazy_segtree(int n, S v) : lazy_segtree(std::vector<S>(n, v)) {}
  explicit lazy_segtree(const std::vector<S>& v) : n(int(v.size())) {
    sz = (int)std::bit_ceil((unsigned int)(n));
    log = std::countr_zero((unsigned int)(sz));
    d = std::vector<S>(2 * sz);
    lz = std::vector<F>(sz);
    for (int i = 0; i < n; i++) d[sz + i] = v[i];
    for (int i = sz - 1; i >= 1; i--) update(i);
  }

  void set(int i, S x) {
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
    if (l == r) return M::e();

    l += sz;
    r += sz;

    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }

    S prodl = M::e(), prodr = M::e();
    while (l < r) {
      if (l & 1) prodl = M::op(prodl, d[l++]);
      if (r & 1) prodr = M::op(d[--r], prodr);
      l >>= 1;
      r >>= 1;
    }

    return M::op(prodl, prodr);
  }

  S all_prod() const { return d[1]; }

  void apply(int i, F f) {
    assert(0 <= i && i < n);
    i += sz;
    for (int j = log; j >= 1; j--) push(i >> j);
    d[i] = M::mapping(f, d[i]);
    for (int j = 1; j <= log; j++) update(i >> j);
  }

  void apply(int l, int r, F f) {
    assert(0 <= l && l <= r && r <= n);
    if (l == r) return;

    l += sz;
    r += sz;

    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }

    {
      int _l = l, _r = r;
      while (l < r) {
        if (l & 1) all_apply(l++, f);
        if (r & 1) all_apply(--r, f);
        l >>= 1;
        r >>= 1;
      }
      l = _l;
      r = _r;
    }

    for (int i = 1; i <= log; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }

  template <bool (*g)(S)> int max_right(int l) {
    return max_right(l, [](S x) { return g(x); });
  }

  template <class G> int max_right(int l, G g) {
    assert(0 <= l && l <= n);
    assert(g(M::e()));
    if (l == n) return n;
    l += sz;
    for (int i = log; i >= 1; i--) push(l >> i);
    S product = M::e();
    do {
      while (l % 2 == 0) l >>= 1;
      if (!g(M::op(product, d[l]))) {
        while (l < sz) {
          push(l);
          l = 2 * l;
          if (g(M::op(product, d[l]))) {
            product = M::op(product, d[l]);
            l++;
          }
        }
        return l - sz;
      }
      product = M::op(product, d[l]);
      l++;
    } while ((l & -l) != l);
    return n;
  }

  template <bool (*g)(S)> int min_left(int r) {
    return min_left(r, [](S x) { return g(x); });
  }

  template <class G> int min_left(int r, G g) {
    assert(0 <= r && r <= n);
    assert(g(M::e()));
    if (r == 0) return 0;
    r += sz;
    for (int i = log; i >= 1; i--) push((r - 1) >> i);
    S product = M::e();
    do {
      r--;
      while (r > 1 && r % 2) r >>= 1;
      if (!g(M::op(d[r], product))) {
        while (r < sz) {
          push(r);
          r = 2 * r + 1;
          if (g(M::op(d[r], product))) {
            product = M::op(d[r], product);
            r--;
          }
        }
        return r + 1 - sz;
      }
      product = M::op(d[r], product);
    } while ((r & -r) != r);
    return 0;
  }

  int size() const { return n; }

private:
  int n, sz, log;
  std::vector<S> d;
  std::vector<F> lz;

  void update(int k) {
    d[k] = M::op(d[2 * k], d[2 * k + 1]);
  }
  void all_apply(int k, F f) {
    d[k] = M::mapping(f, d[k]);
    if (k < sz) lz[k] = M::composition(f, lz[k]);
  }
  void push(int k) {
    all_apply(2 * k, lz[k]);
    all_apply(2 * k + 1, lz[k]);
    lz[k] = M::id();
  }
};

} // namespace cp