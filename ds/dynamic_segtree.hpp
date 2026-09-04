#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "util/io_utility_base.hpp"

namespace cp {

template <class S, auto op, auto e> class dynamic_segtree {
  using ull = unsigned long long;

 public:
  dynamic_segtree() : dynamic_segtree(0) {}
  explicit dynamic_segtree(ull _n, S val = e()) : n(_n) {
    assert(n <= (1ULL << 63));
    sz = std::bit_ceil(n);
    log = std::countr_zero(sz);
    initial_vals.resize(log + 1);
    for (int i = 0; i <= log; i++) {
      initial_vals[i] = val;
      val = op(val, val);
    }
  }

  void set(ull i, const S& x) {
    assert(i < n);
    set(root, 0, sz, log, i, x);
  }

  S operator[](ull i) const {
    assert(i < n);
    return get(root, 0, sz, log, i);
  }

  S prod(ull l, ull r) const {
    assert(l <= r && r <= n);
    return prod(root, 0, sz, log, l, r);
  }

  S all_prod() const { return root ? root->val : initial_vals.back(); }

  template <class F> ull max_right(ull l, F f) const {
    assert(l <= n);
    assert(f(e()));
    S product = e();
    return max_right(root, 0, sz, log, l, f, product);
  }

  template <class F> ull min_left(ull r, F f) const {
    assert(r <= n);
    assert(f(e()));
    S product = e();
    return min_left(root, 0, sz, log, r, f, product);
  }

  ull size() const { return n; }

  friend std::ostream& operator<<(std::ostream& os,
                                  const dynamic_segtree& seg) {
    using io_utility::operator<<;
    std::vector<S> v(seg.n);
    for (int i = 0; i < seg.n; i++) v[i] = seg[i];
    return os << v;
  }

 private:
  struct node;
  using node_ptr = std::unique_ptr<node>;
  struct node {
    S val;
    node_ptr left, right;
    node() {}
    explicit node(const S& v) : val(v) {}
  };
  ull n, sz;
  int log;
  std::vector<S> initial_vals;
  node_ptr root = nullptr;

  void update(node_ptr& t, int h) {
    t->val = op(t->left ? t->left->val : initial_vals[h - 1],
                t->right ? t->right->val : initial_vals[h - 1]);
  }

  void set(node_ptr& t, ull a, ull b, int h, ull i, const S& x) {
    if (!t) t = std::make_unique<node>(initial_vals[h]);
    if (b - a == 1) {
      t->val = x;
      return;
    }
    ull c = (a + b) / 2;
    if (i < c) {
      set(t->left, a, c, h - 1, i, x);
    } else {
      set(t->right, c, b, h - 1, i, x);
    }
    update(t, h);
  }

  S get(const node_ptr& t, ull a, ull b, int h, ull i) const {
    if (!t) return initial_vals[0];
    if (b - a == 1) return t->val;
    ull c = (a + b) / 2;
    if (i < c) {
      return get(t->left, a, c, h - 1, i);
    } else {
      return get(t->right, c, b, h - 1, i);
    }
  }

  S prod(const node_ptr& t, ull a, ull b, int h, ull l, ull r) const {
    if (b <= l || r <= a) return e();
    if (l <= a && b <= r) return t ? t->val : initial_vals[h];
    if (!t) {
      S res = e();
      ull len = std::min(b, r) - std::max(a, l);
      for (int k = 0; len; k++) {
        if (len & 1) res = op(res, initial_vals[k]);
        len >>= 1;
      }
      return res;
    }
    if (l <= a && b <= r) return t->val;
    ull c = (a + b) / 2;
    return op(prod(t->left, a, c, h - 1, l, r),
              prod(t->right, c, b, h - 1, l, r));
  }

  template <class F>
  ull max_right(const node_ptr& t, ull a, ull b, int h, ull l, F f,
                S& product) const {
    if (b <= l) return b;
    if (n <= a) return n;
    if (l <= a && b <= n) {
      S val = t ? t->val : initial_vals[h];
      if (f(op(product, val))) {
        product = op(product, val);
        return b;
      }
    }
    if (b - a == 1) return a;
    if (!t) {
      ull res = std::max(a, l);
      for (int k = h; k >= 0; k--) {
        if (res + (1ULL << k) > std::min(b, n)) continue;
        if (f(op(product, initial_vals[k]))) {
          product = op(product, initial_vals[k]);
          res += 1ULL << k;
        }
      }
      return res;
    }
    ull c = (a + b) / 2;
    ull test = max_right(t->left, a, c, h - 1, l, f, product);
    return test < c ? test : max_right(t->right, c, b, h - 1, l, f, product);
  }

  template <class F>
  ull min_left(const node_ptr& t, ull a, ull b, int h, ull r, F f,
               S& product) const {
    if (r <= a) return a;
    if (b <= r) {
      S val = t ? t->val : initial_vals[h];
      if (f(op(val, product))) {
        product = op(val, product);
        return a;
      }
    }
    if (b - a == 1) return b;
    if (!t) {
      ull res = std::min(b, r);
      for (int k = h; k >= 0; k--) {
        if (res < a + (1ULL << k)) continue;
        if (f(op(initial_vals[k], product))) {
          product = op(initial_vals[k], product);
          res -= 1ULL << k;
        }
      }
      return res;
    }
    ull c = (a + b) / 2;
    ull test = min_left(t->right, c, b, h - 1, r, f, product);
    return test > c ? test : min_left(t->left, a, c, h - 1, r, f, product);
  }
};

}  // namespace cp