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
  explicit dynamic_segtree(ull _n) : dynamic_segtree(_n, e()) {}
  explicit dynamic_segtree(ull _n, S val) : n(_n) {
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

  S operator[](ull i) const {
    assert(i < n);
    return get(root, 0, sz, 0, i);
  }

  S prod(ull l, ull r) const {
    assert(l <= r && r <= n);
    return prod(root, 0, sz, 0, l, r);
  }

  S all_prod() const { return root ? root->val : initial_vals[0]; }

  template <class F> ull max_right(ull l, F f) const {
    assert(l <= n);
    assert(f(e()));
    S product = e();
    return max_right(root, 0, sz, 0, product, l, f);
  }

  template <class F> ull min_left(ull r, F f) const {
    assert(r <= n);
    assert(f(e()));
    S product = e();
    return min_left(root, 0, sz, 0, product, r, f);
  }

  ull size() const { return n; }

  friend std::ostream& operator<<(std::ostream& os,
                                  const dynamic_segtree& seg) {
    std::vector<std::string> outs(seg.n);
    std::ostringstream oss;
    for (int i = 0; i < int(outs.size()); i++) {
      oss << seg[i];
      outs[i] = oss.str();
      oss.str("");
    }
    return os << internal::combine_outputs(outs);
  }

 private:
  struct node;
  using node_ptr = std::unique_ptr<node>;
  struct node {
    S val;
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

  S pow_initial(ull len, int dep) const {
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
    ull c = (a + b) / 2;
    if (i < c) {
      set(p->left, a, c, dep + 1, i, x);
    } else {
      set(p->right, c, b, dep + 1, i, x);
    }
    update(p, dep);
  }

  S get(const node_ptr& p, ull a, ull b, int dep, ull i) const {
    if (!p) return initial_vals.back();
    if (b - a == 1) return p->val;
    ull c = (a + b) / 2;
    if (i < c) {
      return get(p->left, a, c, dep + 1, i);
    } else {
      return get(p->right, c, b, dep + 1, i);
    }
  }

  S prod(const node_ptr& p, ull a, ull b, int dep, ull l, ull r) const {
    if (b <= l || r <= a) return e();
    if (l <= a && b <= r) return p ? p->val : initial_vals[dep];
    if (!p) return pow_initial(std::min(b, r) - std::max(a, l), dep);
    if (l <= a && b <= r) return p->val;
    ull c = (a + b) / 2;
    return op(prod(p->left, a, c, dep + 1, l, r),
              prod(p->right, c, b, dep + 1, l, r));
  }

  template <class F>
  ull max_right(const node_ptr& p, ull a, ull b, int dep, S& product, ull l,
                F f) const {
    if (b <= l) return b;
    if (n <= a) return n;
    if (l <= a && b <= n) {
      S val = p ? p->val : initial_vals[dep];
      if (f(op(product, val))) {
        product = op(product, val);
        return b;
      }
    }
    if (b - a == 1) return a;
    if (!p) {
      ull res = std::max(a, l);
      for (int k = log - dep; k >= 0; k--) {
        if (res + (1ULL << k) > std::min(b, n)) continue;
        if (f(op(product, initial_vals[log - k]))) {
          product = op(product, initial_vals[log - k]);
          res += 1ULL << k;
        }
      }
      return res;
    }
    ull c = (a + b) / 2;
    ull test = max_right(p->left, a, c, dep + 1, product, l, f);
    return test < c ? test : max_right(p->right, c, b, dep + 1, product, l, f);
  }

  template <class F>
  ull min_left(const node_ptr& p, ull a, ull b, int dep, S& product, ull r,
               F f) const {
    if (r <= a) return a;
    if (b <= r) {
      S val = p ? p->val : initial_vals[dep];
      if (f(op(val, product))) {
        product = op(val, product);
        return a;
      }
    }
    if (b - a == 1) return b;
    if (!p) {
      ull res = std::min(b, r);
      for (int k = log - dep; k >= 0; k--) {
        if (res < a + (1ULL << k)) continue;
        if (f(op(initial_vals[log - k], product))) {
          product = op(initial_vals[log - k], product);
          res -= 1ULL << k;
        }
      }
      return res;
    }
    ull c = (a + b) / 2;
    ull test = min_left(p->right, c, b, dep + 1, product, r, f);
    return test > c ? test : min_left(p->left, a, c, dep + 1, product, r, f);
  }
};

}  // namespace cp