#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "util/io_utility.hpp"

namespace cp {

template <class S, auto op, auto e> class persistent_segtree {
  using ull = unsigned long long;
  class node;

 public:
  using node_ptr = node*;

  persistent_segtree() : persistent_segtree(0) {}
  explicit persistent_segtree(ull _n, S val = e()) : n(_n) {
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
    node* t = root;
    std::vector<node*> ps(log);
    for (int h = log - 1; t && h >= 0; h--) {
      ps[h] = t;
      t = !((i >> h) & 1) ? t->left : t->right;
    }
    node* cur = new node(x);
    for (int h = 0; h < log; h++) {
      node* nxt = ps[h] ? new node(*ps[h]) : new node();
      (!((i >> h) & 1) ? nxt->left : nxt->right) = cur;
      update(nxt, h + 1);
      cur = nxt;
    }
    root = cur;
  }

  S operator[](ull i) const {
    assert(i < n);
    node* t = root;
    for (int h = log - 1; t && h >= 0; h--) {
      t = !((i >> h) & 1) ? t->left : t->right;
    }
    return t ? t->val : initial_vals[0];
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

  node* snapshot() const { return root; }
  void restore(node* new_root) { root = new_root; }

  friend std::ostream& operator<<(std::ostream& os,
                                  const persistent_segtree& seg) {
    std::vector<S> v(seg.n);
    for (int i = 0; i < seg.n; i++) v[i] = seg[i];
    return os << v;
  }

 private:
  class node {
   private:
    friend persistent_segtree;
    S val;
    node* left = nullptr;
    node* right = nullptr;
    node() : val(e()) {}
    node(const S& x) : val(x) {}
  }* root = nullptr;
  ull n, sz;
  int log;
  std::vector<S> initial_vals;

  void update(node* t, int h) {
    t->val = op(t->left ? t->left->val : initial_vals[h - 1],
                t->right ? t->right->val : initial_vals[h - 1]);
  }

  S prod(const node* t, ull a, ull b, int h, ull l, ull r) const {
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
  ull max_right(const node* t, ull a, ull b, int h, ull l, F f,
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
  ull min_left(const node* t, ull a, ull b, int h, ull r, F f,
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