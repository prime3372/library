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

  void update(node_ptr& p, int h) {
    p->val = op(p->left ? p->left->val : initial_vals[h - 1],
                p->right ? p->right->val : initial_vals[h - 1]);
  }
  void all_apply(node_ptr& p, F f) {
    p->val = act(f, p->val);
    p->lz = compose(f, p->lz);
    p->lzflag = true;
  }
  void push(node_ptr& p, int h) {
    if (!p->lzflag) return;
    if (!p->left) p->left = std::make_unique<node>(initial_vals[h - 1]);
    if (!p->right) p->right = std::make_unique<node>(initial_vals[h - 1]);
    all_apply(p->left, p->lz);
    all_apply(p->right, p->lz);
    p->lz = id();
    p->lzflag = false;
  }

  void set(node_ptr& p, ull a, ull b, int h, ull i, S x) {
    if (!p) p = std::make_unique<node>(initial_vals[h]);
    if (b - a == 1) {
      p->val = x;
      return;
    }
    push(p, h);
    ull c = (a + b) / 2;
    if (i < c) {
      set(p->left, a, c, h - 1, i, x);
    } else {
      set(p->right, c, b, h - 1, i, x);
    }
    update(p, h);
  }

  S get(node_ptr& p, ull a, ull b, int h, ull i) {
    if (!p) return initial_vals[0];
    if (b - a == 1) return p->val;
    push(p, h);
    ull c = (a + b) / 2;
    if (i < c) {
      return get(p->left, a, c, h - 1, i);
    } else {
      return get(p->right, c, b, h - 1, i);
    }
  }

  S prod(node_ptr& p, ull a, ull b, int h, ull l, ull r) {
    if (b <= l || r <= a) return e();
    if (l <= a && b <= r) return p ? p->val : initial_vals[h];
    if (!p) {
      S res = e();
      ull len = std::min(b, r) - std::max(a, l);
      for (int k = 0; len; k++) {
        if (len & 1) res = op(res, initial_vals[k]);
        len >>= 1;
      }
      return res;
    }
    push(p, h);
    ull c = (a + b) / 2;
    return op(prod(p->left, a, c, h - 1, l, r),
              prod(p->right, c, b, h - 1, l, r));
  }

  void apply(node_ptr& p, ull a, ull b, int h, ull i, F f) {
    if (!p) p = std::make_unique<node>(initial_vals[h]);
    if (b - a == 1) {
      p->val = act(f, p->val);
      return;
    }
    push(p, h);
    ull c = (a + b) / 2;
    if (i < c) {
      apply(p->left, a, c, h - 1, i, f);
    } else {
      apply(p->right, c, b, h - 1, i, f);
    }
    update(p, h);
  }

  void apply(node_ptr& p, ull a, ull b, int h, ull l, ull r, F f) {
    if (b <= l || r <= a) return;
    if (!p) p = std::make_unique<node>(initial_vals[h]);
    if (l <= a && b <= r) {
      all_apply(p, f);
      return;
    }
    push(p, h);
    ull c = (a + b) / 2;
    apply(p->left, a, c, h - 1, l, r, f);
    apply(p->right, c, b, h - 1, l, r, f);
    update(p, h);
  }

  template <class G>
  ull max_right(node_ptr& p, ull a, ull b, int h, ull l, G g, S& product) {
    if (b <= l) return b;
    if (n <= a) return n;
    if (l <= a && b <= n) {
      S val = p ? p->val : initial_vals[h];
      if (g(op(product, val))) {
        product = op(product, val);
        return b;
      }
    }
    if (b - a == 1) return a;
    if (!p) {
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
    push(p, h);
    ull c = (a + b) / 2;
    ull test = max_right(p->left, a, c, h - 1, l, g, product);
    return test < c ? test : max_right(p->right, c, b, h - 1, l, g, product);
  }

  template <class G>
  ull min_left(node_ptr& p, ull a, ull b, int h, ull r, G g, S& product) {
    if (r <= a) return a;
    if (b <= r) {
      S val = p ? p->val : initial_vals[h];
      if (g(op(val, product))) {
        product = op(val, product);
        return a;
      }
    }
    if (b - a == 1) return b;
    if (!p) {
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
    push(p, h);
    ull c = (a + b) / 2;
    ull test = min_left(p->right, c, b, h - 1, r, g, product);
    return test > c ? test : min_left(p->left, a, c, h - 1, r, g, product);
  }
};

}  // namespace cp