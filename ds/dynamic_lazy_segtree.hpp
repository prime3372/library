#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "util/io_utility.hpp"

namespace cp {

template <class S, auto op, auto e, class F, auto act, auto compose, auto id>
class dynamic_lazy_segtree {
  using ull = unsigned long long;

 public:
  dynamic_lazy_segtree() : dynamic_lazy_segtree(0) {}
  explicit dynamic_lazy_segtree(ull _n, S val = e()) : n(_n) {
    assert(n <= (1ULL << 63));
    sz = std::bit_ceil(n);
    log = std::countr_zero(sz);
    initial_vals.resize(log + 1);
    for (int i = 0; i <= log; i++) {
      initial_vals[i] = val;
      val = op(val, val);
    }
  }
  dynamic_lazy_segtree(const dynamic_lazy_segtree& other)
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
  dynamic_lazy_segtree(dynamic_lazy_segtree&& other)
      : root(other.root),
        n(other.n),
        sz(other.sz),
        log(other.log),
        initial_vals(std::move(other.initial_vals)) {
    other.root = nullptr;
    other.n = other.sz = other.log = 0;
  }
  dynamic_lazy_segtree operator=(dynamic_lazy_segtree other) {
    std::swap(root, other.root);
    std::swap(n, other.n);
    std::swap(sz, other.sz);
    std::swap(log, other.log);
    std::swap(initial_vals, other.initial_vals);
    return *this;
  }
  ~dynamic_lazy_segtree() {
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
    set(root, 0, sz, log, i, x);
  }

  S operator[](ull i) {
    assert(i < n);
    return get(root, 0, sz, log, i);
  }

  S prod(ull l, ull r) {
    assert(l <= r && r <= n);
    return prod(root, 0, sz, log, l, r);
  }

  S all_prod() { return root ? root->val : initial_vals[log]; }

  void apply(ull i, const F& f) {
    assert(i < n);
    apply(root, 0, sz, log, i, f);
  }

  void apply(ull l, ull r, const F& f) {
    assert(l <= r && r <= n);
    apply(root, 0, sz, log, l, r, f);
  }

  template <class G> ull max_right(ull l, const G& g) {
    assert(l <= n);
    assert(g(e()));
    S product = e();
    return max_right(root, 0, sz, log, l, g, product);
  }

  template <class G> ull min_left(ull r, const G& g) {
    assert(r <= n);
    assert(g(e()));
    S product = e();
    return min_left(root, 0, sz, log, r, g, product);
  }

  ull size() const { return n; }

  friend std::ostream& operator<<(std::ostream& os, dynamic_lazy_segtree seg) {
    std::vector<S> v(seg.n);
    for (int i = 0; i < seg.n; i++) v[i] = seg[i];
    return os << v;
  }

 private:
  struct node {
    S val;
    F lz = id();
    bool lzflag = false;
    node* left = nullptr;
    node* right = nullptr;
    node(const S& x) : val(x) {}
  }* root = nullptr;
  ull n, sz;
  int log;
  std::vector<S> initial_vals;

  void update(node* t, int h) {
    t->val = op(t->left ? t->left->val : initial_vals[h - 1],
                t->right ? t->right->val : initial_vals[h - 1]);
  }
  void all_apply(node* t, const F& f) {
    t->val = act(f, t->val);
    t->lz = compose(f, t->lz);
    t->lzflag = true;
  }
  void push(node* t, int h) {
    if (!t->lzflag) return;
    if (!t->left) t->left = new node(initial_vals[h - 1]);
    if (!t->right) t->right = new node(initial_vals[h - 1]);
    all_apply(t->left, t->lz);
    all_apply(t->right, t->lz);
    t->lz = id();
    t->lzflag = false;
  }

  void set(node*& t, ull a, ull b, int h, ull i, const S& x) {
    if (!t) t = new node(initial_vals[h]);
    if (b - a == 1) {
      t->val = x;
      return;
    }
    push(t, h);
    ull c = (a + b) / 2;
    if (i < c) {
      set(t->left, a, c, h - 1, i, x);
    } else {
      set(t->right, c, b, h - 1, i, x);
    }
    update(t, h);
  }

  S get(node* t, ull a, ull b, int h, ull i) {
    if (!t) return initial_vals[0];
    if (b - a == 1) return t->val;
    push(t, h);
    ull c = (a + b) / 2;
    if (i < c) {
      return get(t->left, a, c, h - 1, i);
    } else {
      return get(t->right, c, b, h - 1, i);
    }
  }

  S prod(node* t, ull a, ull b, int h, ull l, ull r) {
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
    push(t, h);
    ull c = (a + b) / 2;
    return op(prod(t->left, a, c, h - 1, l, r),
              prod(t->right, c, b, h - 1, l, r));
  }

  void apply(node*& t, ull a, ull b, int h, ull i, const F& f) {
    if (!t) t = new node(initial_vals[h]);
    if (b - a == 1) {
      t->val = act(f, t->val);
      return;
    }
    push(t, h);
    ull c = (a + b) / 2;
    if (i < c) {
      apply(t->left, a, c, h - 1, i, f);
    } else {
      apply(t->right, c, b, h - 1, i, f);
    }
    update(t, h);
  }

  void apply(node*& t, ull a, ull b, int h, ull l, ull r, const F& f) {
    if (b <= l || r <= a) return;
    if (!t) t = new node(initial_vals[h]);
    if (l <= a && b <= r) {
      all_apply(t, f);
      return;
    }
    push(t, h);
    ull c = (a + b) / 2;
    apply(t->left, a, c, h - 1, l, r, f);
    apply(t->right, c, b, h - 1, l, r, f);
    update(t, h);
  }

  template <class G>
  ull max_right(node* t, ull a, ull b, int h, ull l, const G& g, S& product) {
    if (b <= l) return b;
    if (n <= a) return n;
    if (l <= a && b <= n) {
      S val = t ? t->val : initial_vals[h];
      if (g(op(product, val))) {
        product = op(product, val);
        return b;
      }
    }
    if (b - a == 1) return a;
    if (!t) {
      ull res = std::max(a, l);
      for (int k = h; k >= 0; k--) {
        if (res + (1ULL << k) > std::min(b, n)) continue;
        if (g(op(product, initial_vals[k]))) {
          product = op(product, initial_vals[k]);
          res += 1ULL << k;
        }
      }
      return res;
    }
    push(t, h);
    ull c = (a + b) / 2;
    ull test = max_right(t->left, a, c, h - 1, l, g, product);
    return test < c ? test : max_right(t->right, c, b, h - 1, l, g, product);
  }

  template <class G>
  ull min_left(node* t, ull a, ull b, int h, ull r, const G& g, S& product) {
    if (r <= a) return a;
    if (b <= r) {
      S val = t ? t->val : initial_vals[h];
      if (g(op(val, product))) {
        product = op(val, product);
        return a;
      }
    }
    if (b - a == 1) return b;
    if (!t) {
      ull res = std::min(b, r);
      for (int k = h; k >= 0; k--) {
        if (res < a + (1ULL << k)) continue;
        if (g(op(initial_vals[k], product))) {
          product = op(initial_vals[k], product);
          res -= 1ULL << k;
        }
      }
      return res;
    }
    push(t, h);
    ull c = (a + b) / 2;
    ull test = min_left(t->right, c, b, h - 1, r, g, product);
    return test > c ? test : min_left(t->left, a, c, h - 1, r, g, product);
  }
};

}  // namespace cp