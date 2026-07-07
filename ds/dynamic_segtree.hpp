#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <memory>
#include <vector>

#include "algebra/monoid.hpp"

namespace cp {

template <monoid M> struct dynamic_segtree {
private:
  using S = typename M::S;

public:
  dynamic_segtree() : dynamic_segtree(0) {}
  explicit dynamic_segtree(size_t _n) : dynamic_segtree(_n, M::e()) {}
  explicit dynamic_segtree(size_t _n, S v) : n(_n), root(nullptr) {
    sz = std::bit_ceil(n);
    log = std::countr_zero(sz);
    initial_vals.resize(log + 1);
    for (int i = log; i >= 0; i--) {
      initial_vals[i] = v;
      v = M::op(v, v);
    }
  }

  void set(size_t i, S x) {
    assert(i < n);
    set(root, 0, sz, 0, i, x);
  }

  S operator[](size_t i) const {
    assert(i < n);
    return get(root, 0, sz, 0, i);
  }

  S prod(size_t l, size_t r) {
    assert(l <= r && r <= n);
    return prod(root, 0, sz, 0, l, r);
  }

  S all_prod() const { return root ? root->val : initial_vals[0]; }

  template <bool (*f)(S)> size_t max_right(size_t l) {
    return max_right(l, [](S x) { return f(x); });
  }
  template <class F> size_t max_right(size_t l, F f) {
    assert(l <= n);
    assert(f(M::e()));
    S product = M::e();
    return max_right(root, 0, sz, 0, product, l, f);
  }

  template <bool (*f)(S)> size_t min_left(size_t r) {
    return min_left(r, [](S x) { return f(x); });
  }
  template <class F> size_t min_left(size_t r, F f) {
    assert(r <= n);
    assert(f(M::e()));
    S product = M::e();
    return min_left(root, 0, sz, 0, product, r, f);
  }

  size_t size() const { return n; }

private:
  struct node;
  using node_ptr = std::unique_ptr<node>;
  struct node {
    S val;
    node_ptr left, right;
    node(S v) : val(v), left(nullptr), right(nullptr) {}
  };
  size_t n, sz;
  int log;
  node_ptr root;
  std::vector<S> initial_vals;

  void update(node_ptr& p, int dep) {
    p->val = M::op(p->left ? p->left->val : initial_vals[dep + 1],
                   p->right ? p->right->val : initial_vals[dep + 1]);
  }

  S pow_initial(size_t len, int dep) {
    S res = M::e();
    for (int k = 0; k <= log - dep; k++) {
      if (len & 1) res = M::op(res, initial_vals[log - k]);      
      len >>= 1;
    }
    return res;
  }

  void set(node_ptr& p, size_t a, size_t b, int dep, size_t i, S x) {
    if (!p) p = std::make_unique<node>(initial_vals[dep]);
    if (b - a == 1) {
      p->val = x;
      return;
    }
    size_t c = (a + b) / 2;
    if (i < c) set(p->left, a, c, dep + 1, i, x);
    else set(p->right, c, b, dep + 1, i, x);
    update(p, dep);
  }

  S get(const node_ptr& p, size_t a, size_t b, int dep, size_t i) const {
    if (!p) return initial_vals.back();
    if (b - a == 1) return p->val;
    size_t c = (a + b) / 2;
    if (i < c) return get(p->left, a, c, dep + 1, i);
    else return get(p->right, c, b, dep + 1, i);
  }

  S prod(const node_ptr& p, size_t a, size_t b, int dep, size_t l, size_t r) {
    if (b <= l || r <= a) return M::e();
    if (l <= a && b <= r) return p ? p->val : initial_vals[dep];
    if (!p) return pow_initial(std::min(b, r) - std::max(a, l), dep);
    if (l <= a && b <= r) return p->val;
    size_t c = (a + b) / 2;
    return M::op(prod(p->left, a, c, dep + 1, l, r),
                 prod(p->right, c, b, dep + 1, l, r));
  }

  template <class F>
  size_t max_right(const node_ptr& p, size_t a, size_t b, int dep, S& product, size_t l, F f) {
    if (b <= l) return b;
    if (n <= a) return n;
    if (l <= a && b <= n) {
      S val = p ? p->val : initial_vals[dep];
      if (f(M::op(product, val))) {
        product = M::op(product, val);
        return b;
      }
    }
    if (b - a == 1) return a;
    if (!p) {
      size_t res = std::max(a, l);
      for (int k = log - dep; k >= 0; k--) {
        if (res + (1ULL << k) > std::min(b, n)) continue;
        if (f(M::op(product, initial_vals[log - k]))) {
          product = M::op(product, initial_vals[log - k]);
          res += 1ULL << k;
        }
      }
      return res;
    }
    size_t c = (a + b) / 2;
    size_t test = max_right(p->left, a, c, dep + 1, product, l, f);
    return test < c ? test : max_right(p->right, c, b, dep + 1, product, l, f);
  }

  template <class F>
  size_t min_left(const node_ptr& p, size_t a, size_t b, int dep, S& product, size_t r, F f) {
    if (r <= a) return a;
    if (b <= r) {
      S val = p ? p->val : initial_vals[dep];
      if (f(M::op(val, product))) {
        product = M::op(val, product);
        return a;
      }
    }
    if (b - a == 1) return b;
    if (!p) {
      size_t res = std::min(b, r);
      for (int k = log - dep; k >= 0; k--) {
        if (res < a + (1ULL << k)) continue;
        if (f(M::op(initial_vals[log - k], product))) {
          product = M::op(initial_vals[log - k], product);
          res -= 1ULL << k;
        }
      }
      return res;
    }
    size_t c = (a + b) / 2;
    size_t test = min_left(p->right, c, b, dep + 1, product, r, f);
    return test > c ? test : min_left(p->left, a, c, dep + 1, product, r, f);
  }
};

} // namespace cp