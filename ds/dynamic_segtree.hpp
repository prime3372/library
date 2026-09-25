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
  dynamic_segtree(const dynamic_segtree& other)
      : n(other.n),
        sz(other.sz),
        log(other.log),
        initial_vals(other.initial_vals) {
    auto dfs = [&](auto self, const node* t) -> node* {
      if (!t) return nullptr;
      node* ptr = new node(*t);
      ptr->left = self(self, t->left);
      ptr->right = self(self, t->right);
      return ptr;
    };
    root = dfs(dfs, other.root);
  }
  dynamic_segtree(dynamic_segtree&& other) noexcept
      : root(other.root),
        n(other.n),
        sz(other.sz),
        log(other.log),
        initial_vals(std::move(other.initial_vals)) {
    other.root = nullptr;
    other.n = other.sz = other.log = 0;
  }
  dynamic_segtree& operator=(dynamic_segtree other) {
    std::swap(root, other.root);
    std::swap(n, other.n);
    std::swap(sz, other.sz);
    std::swap(log, other.log);
    std::swap(initial_vals, other.initial_vals);
    return *this;
  }
  ~dynamic_segtree() {
    auto dfs = [&](auto self, node* t) -> void {
      if (!t) return;
      self(self, t->left);
      self(self, t->right);
      delete t;
    };
    dfs(dfs, root);
  }

  void set(ull i, const S& x) {
    assert(i < n);
    node* t = root;
    std::vector<node*> ps(log);
    for (int h = log - 1; t && h >= 0; h--) {
      ps[h] = t;
      t = ((i >> h) & 1 ? t->right : t->left);
    }
    node* cur = t ? (t->val = x, t) : new node(x);
    for (int h = 0; h < log; h++) {
      node* nxt = ps[h] ? ps[h] : new node();
      ((i >> h) & 1 ? nxt->right : nxt->left) = cur;
      update(nxt, h + 1);
      cur = nxt;
    }
    root = cur;
  }

  S operator[](ull i) const {
    assert(i < n);
    node* t = root;
    for (int h = log - 1; t && h >= 0; h--) {
      t = ((i >> h) & 1 ? t->right : t->left);
    }
    return t ? t->val : initial_vals[0];
  }

  S prod(ull l, ull r) const {
    assert(l <= r && r <= n);
    return prod(root, 0, sz, l, r, log);
  }

  S all_prod() const { return prod(0, n); }

  template <class F> ull max_right(ull l, F f) const {
    assert(l <= n);
    assert(f(e()));
    S product = e();
    return max_right(root, 0, sz, l, log, f, product);
  }

  template <class F> ull min_left(ull r, F f) const {
    assert(r <= n);
    assert(f(e()));
    S product = e();
    return min_left(root, 0, sz, r, log, f, product);
  }

  ull size() const { return n; }

  friend std::ostream& operator<<(std::ostream& os,
                                  const dynamic_segtree& seg) {
    std::vector<S> v(seg.n);
    for (ull i = 0; i < seg.n; i++) v[i] = seg[i];
    return os << v;
  }

 private:
  struct node {
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

  S prod(const node* t, ull a, ull b, ull l, ull r, int h) const {
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
    ull c = (a + b) / 2;
    return op(prod(t->left, a, c, l, r, h - 1),
              prod(t->right, c, b, l, r, h - 1));
  }

  template <class F>
  ull max_right(const node* t, ull a, ull b, ull l, int h, F f,
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
    ull test = max_right(t->left, a, c, l, h - 1, f, product);
    return test < c ? test : max_right(t->right, c, b, l, h - 1, f, product);
  }

  template <class F>
  ull min_left(const node* t, ull a, ull b, ull r, int h, F f,
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
    ull test = min_left(t->right, c, b, r, h - 1, f, product);
    return test > c ? test : min_left(t->left, a, c, r, h - 1, f, product);
  }
};

}  // namespace cp