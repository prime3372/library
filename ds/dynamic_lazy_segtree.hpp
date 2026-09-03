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
    for (int i = log; i >= 0; i--) {
      initial_vals[i] = val;
      val = op(val, val);
    }
  }

  void set(ull i, S x) {
    assert(i < n);
    set(root, 0, sz, 0, i, x);
  }

  S operator[](ull i) {
    assert(i < n);
    return get(root, 0, sz, 0, i);
  }

  S prod(ull l, ull r) {
    assert(l <= r && r <= n);
    return prod(root, 0, sz, 0, l, r);
  }

  S all_prod() { return root ? root->val : initial_vals[0]; }

  void apply(ull i, F f) {
    assert(i < n);
    apply(root, 0, sz, 0, i, f);
  }

  void apply(ull l, ull r, F f) {
    assert(l <= r && r <= n);
    apply(root, 0, sz, 0, l, r, f);
  }

  template <class G> ull max_right(ull l, G g) {
    assert(l <= n);
    assert(g(e()));
    S product = e();
    return max_right(root, 0, sz, 0, product, l, g);
  }

  template <class G> ull min_left(ull r, G g) {
    assert(r <= n);
    assert(g(e()));
    S product = e();
    return min_left(root, 0, sz, 0, product, r, g);
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
    node(S v) : val(v) {}
  };
  ull n, sz;
  int log;
  std::vector<S> initial_vals;
  node_ptr root = nullptr;

  void update(node_ptr& p, int dep) {
    p->val = op(p->left ? p->left->val : initial_vals[dep + 1],
                p->right ? p->right->val : initial_vals[dep + 1]);
  }
  void all_apply(node_ptr& p, F f) {
    p->val = act(f, p->val);
    p->lz = compose(f, p->lz);
    p->lzflag = true;
  }
  void push(node_ptr& p, int dep) {
    if (!p->lzflag) return;
    if (!p->left) p->left = std::make_unique<node>(initial_vals[dep + 1]);
    if (!p->right) p->right = std::make_unique<node>(initial_vals[dep + 1]);
    all_apply(p->left, p->lz);
    all_apply(p->right, p->lz);
    p->lz = id();
    p->lzflag = false;
  }

  S pow_initial(ull len, int dep) {
    S res = e();
    for (int k = 0; k <= log - dep; k++) {
      if (len & 1) res = op(res, initial_vals[log - k]);
      len >>= 1;
    }
    return res;
  }

  void set(node_ptr& p, ull a, ull b, int dep, ull i, S x) {
    if (!p) p = std::make_unique<node>(initial_vals[dep]);
    if (b - a == 1) {
      p->val = x;
      return;
    }
    push(p, dep);
    ull c = (a + b) / 2;
    if (i < c) {
      set(p->left, a, c, dep + 1, i, x);
    } else {
      set(p->right, c, b, dep + 1, i, x);
    }
    update(p, dep);
  }

  S get(node_ptr& p, ull a, ull b, int dep, ull i) {
    if (!p) return initial_vals.back();
    if (b - a == 1) return p->val;
    push(p, dep);
    ull c = (a + b) / 2;
    if (i < c) {
      return get(p->left, a, c, dep + 1, i);
    } else {
      return get(p->right, c, b, dep + 1, i);
    }
  }

  S prod(node_ptr& p, ull a, ull b, int dep, ull l, ull r) {
    if (b <= l || r <= a) return e();
    if (l <= a && b <= r) return p ? p->val : initial_vals[dep];
    if (!p) return pow_initial(std::min(b, r) - std::max(a, l), dep);
    push(p, dep);
    ull c = (a + b) / 2;
    return op(prod(p->left, a, c, dep + 1, l, r),
              prod(p->right, c, b, dep + 1, l, r));
  }

  void apply(node_ptr& p, ull a, ull b, int dep, ull i, F f) {
    if (!p) p = std::make_unique<node>(initial_vals[dep]);
    if (b - a == 1) {
      p->val = act(f, p->val);
      return;
    }
    push(p, dep);
    ull c = (a + b) / 2;
    if (i < c) {
      apply(p->left, a, c, dep + 1, i, f);
    } else {
      apply(p->right, c, b, dep + 1, i, f);
    }
    update(p, dep);
  }

  void apply(node_ptr& p, ull a, ull b, int dep, ull l, ull r, F f) {
    if (b <= l || r <= a) return;
    if (!p) p = std::make_unique<node>(initial_vals[dep]);
    if (l <= a && b <= r) {
      all_apply(p, f);
      return;
    }
    push(p, dep);
    ull c = (a + b) / 2;
    apply(p->left, a, c, dep + 1, l, r, f);
    apply(p->right, c, b, dep + 1, l, r, f);
    update(p, dep);
  }

  template <class G>
  ull max_right(node_ptr& p, ull a, ull b, int dep, S& product, ull l, G g) {
    if (b <= l) return b;
    if (n <= a) return n;
    if (l <= a && b <= n) {
      S val = p ? p->val : initial_vals[dep];
      if (g(op(product, val))) {
        product = op(product, val);
        return b;
      }
    }
    if (b - a == 1) return a;
    if (!p) {
      ull res = std::max(a, l);
      for (int k = log - dep; k >= 0; k--) {
        if (res + (1ULL << k) > std::min(b, n)) continue;
        if (g(op(product, initial_vals[log - k]))) {
          product = op(product, initial_vals[log - k]);
          res += 1ULL << k;
        }
      }
      return res;
    }
    push(p, dep);
    ull c = (a + b) / 2;
    ull test = max_right(p->left, a, c, dep + 1, product, l, g);
    return test < c ? test : max_right(p->right, c, b, dep + 1, product, l, g);
  }

  template <class G>
  ull min_left(node_ptr& p, ull a, ull b, int dep, S& product, ull r, G g) {
    if (r <= a) return a;
    if (b <= r) {
      S val = p ? p->val : initial_vals[dep];
      if (g(op(val, product))) {
        product = op(val, product);
        return a;
      }
    }
    if (b - a == 1) return b;
    if (!p) {
      ull res = std::min(b, r);
      for (int k = log - dep; k >= 0; k--) {
        if (res < a + (1ULL << k)) continue;
        if (g(op(initial_vals[log - k], product))) {
          product = op(initial_vals[log - k], product);
          res -= 1ULL << k;
        }
      }
      return res;
    }
    push(p, dep);
    ull c = (a + b) / 2;
    ull test = min_left(p->right, c, b, dep + 1, product, r, g);
    return test > c ? test : min_left(p->left, a, c, dep + 1, product, r, g);
  }
};

}  // namespace cp