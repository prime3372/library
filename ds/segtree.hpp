#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <type_traits>
#include <vector>
#include "../algebra/monoid.hpp"

template <monoid M> struct segtree {
  using S = typename M::S;

public:
  segtree() : segtree(0) {}
  explicit segtree(int n) : segtree(std::vector<S>(n, M::e())) {}
  template <class T>
    requires std::is_convertible_v<T, S>
  explicit segtree(const std::vector<T>& v) : n(int(v.size())) {
    size = (int)std::bit_ceil((unsigned int)(n));
    log = std::countr_zero((unsigned int)(size));
    d = std::vector<S>(2 * size);
    for (int i = 0; i < n; i++) d[size + i] = v[i];
    for (int i = size - 1; i >= 1; i--) update(i);
  }

  void set(int i, S x) {
    assert(0 <= i && i < n);
    i += size;
    d[i] = x;
    for (int j = 1; j <= log; j++) update(i >> j);
  }

  S operator[](int i) const {
    assert(0 <= i && i < n);
    return d[i + size];
  }

  S prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    S prodl = M::e(), prodr = M::e();
    l += size;
    r += size;

    while (l < r) {
      if (l & 1) prodl = M::op(prodl, d[l++]);
      if (r & 1) prodr = M::op(d[--r], prodr);
      l >>= 1;
      r >>= 1;
    }
    return M::op(prodl, prodr);
  }

  S all_prod() const { return d[1]; }

  template <bool (*f)(S)> int max_right(int l) const {
    return max_right(l, [](S x) { return f(x); });
  }

  template <class F> int max_right(int l, F f) const {
    assert(0 <= l && l <= n);
    assert(f(M::e()));
    if (l == n) return n;
    l += size;
    S product = M::e();
    do {
      while (l % 2 == 0) l >>= 1;
      if (!f(M::op(product, d[l]))) {
        while (l < size) {
          l = 2 * l;
          if (f(M::op(product, d[l]))) {
            product = M::op(product, d[l]);
            l++;
          }
        }
        return l - size;
      }
      product = M::op(product, d[l]);
      l++;
    } while ((l & -l) != l);
    return n;
  }

  template <bool (*f)(S)> int min_left(int r) const {
    return min_left(r, [](S x) { return f(x); });
  }

  template <class F> int min_left(int r, F f) const {
    assert(0 <= r && r <= n);
    assert(f(M::e()));
    if (r == 0) return 0;
    r += size;
    S product = M::e();
    do {
      r--;
      while (r > 1 && r % 2) r >>= 1;
      if (!f(M::op(d[r], product))) {
        while (r < size) {
          r = 2 * r + 1;
          if (f(M::op(d[r], product))) {
            product = M::op(d[r], product);
            r--;
          }
        }
        return r + 1 - size;
      }
      product = M::op(d[r], product);
    } while ((r & -r) != r);
    return 0;
  }

private:
  int n, size, log;
  std::vector<S> d;

  void update(int k) {
    d[k] = M::op(d[2 * k], d[2 * k + 1]);
  }
};
