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

  void set(ull i, S x) {
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

  void apply(ull i, F f) {
    assert(i < n);
    apply(root, 0, sz, log, i, f);
  }

  void apply(ull l, ull r, F f) {
    assert(l <= r && r <= n);
    apply(root, 0, sz, log, l, r, f);
  }

  template <class G> ull max_right(ull l, G g) {
    assert(l <= n);
    assert(g(e()));
    S product = e();
    return max_right(root, 0, sz, log, l, g, product);
  }

  template <class G> ull min_left(ull r, G g) {
    assert(r <= n);
    assert(g(e()));
    S product = e();
    return min_left(root, 0, sz, log, r, g, product);
  }

  ull size() const { return n; }

  friend std::ostream& operator<<(std::ostream& os, dynamic_lazy_segtree seg) {
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
    F lz = id();
    bool lzflag = false;
    node_ptr left, right;
    node() {}
    explicit node(S v) : val(v) {}
  };
  ull n, sz;
  int log;
  std::vector<S> initial_vals;
  node_ptr root = nullptr;

  void update(node_ptr& t, int h) {
    t->val = op(t->left ? t->left->val : initial_vals[h - 1],
                t->right ? t->right->val : initial_vals[h - 1]);
  }
  void all_apply(node_ptr& t, F f) {
    t->val = act(f, t->val);
    t->lz = compose(f, t->lz);
    t->lzflag = true;
  }
  void push(node_ptr& t, int h) {
    if (!t->lzflag) return;
    if (!t->left) t->left = std::make_unique<node>(initial_vals[h - 1]);
    if (!t->right) t->right = std::make_unique<node>(initial_vals[h - 1]);
    all_apply(t->left, t->lz);
    all_apply(t->right, t->lz);
    t->lz = id();
    t->lzflag = false;
  }

  void set(node_ptr& t, ull a, ull b, int h, ull i, S x) {
    if (!t) t = std::make_unique<node>(initial_vals[h]);
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

  S get(node_ptr& t, ull a, ull b, int h, ull i) {
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

  S prod(node_ptr& t, ull a, ull b, int h, ull l, ull r) {
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

  void apply(node_ptr& t, ull a, ull b, int h, ull i, F f) {
    if (!t) t = std::make_unique<node>(initial_vals[h]);
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

  void apply(node_ptr& t, ull a, ull b, int h, ull l, ull r, F f) {
    if (b <= l || r <= a) return;
    if (!t) t = std::make_unique<node>(initial_vals[h]);
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
  ull max_right(node_ptr& t, ull a, ull b, int h, ull l, G g, S& product) {
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
  ull min_left(node_ptr& t, ull a, ull b, int h, ull r, G g, S& product) {
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