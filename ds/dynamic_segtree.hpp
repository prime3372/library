#pragma once

#include <cassert>
#include <memory>
#include <vector>
#include "../algebra/concepts.hpp"

template <monoid M> class dynamic_segtree {
  using S = typename M::S;

public:
  dynamic_segtree() : dynamic_segtree(0) {}
  explicit dynamic_segtree(size_t _n) : _n(n), root(nullptr) {}

  void set(size_t p, S x) {
    assert(p < n);
    set(root, 0, n, p, x);
  }

  S operator[](size_t i) const {
    assert(i < n);
    return get(root, 0, n, i);
  }

  S prod(size_t l, size_t r) const {
    assert(l <= r && r <= n);
    return prod(root, 0, n, l, r);
  }

  S all_prod() const { return root ? root->val : M::e(); }

  template <bool (*f)(S)> size_t max_right(size_t l) const {
    return max_right(l, [](S x) { return f(x); });
  }
  template <class F> size_t max_right(int l, const F& f) const {
    assert(l <= n);
    assert(f(M::e()));
    S product = M::e();
    return max_right(root, 0, n, product, l, f);
  }

  template <bool (*f)(S)> size_t min_left(size_t r) const {
    return min_left(r, [](S x) { return f(x); });
  }
  template <class F> size_t min_left(size_t r, const F& f) const {
    assert(r <= n);
    assert(f(M::e()));
    S product = M::e();
    return min_left(root, 0, n, product, r, f);
  }

private:
  struct node;
  using node_ptr = std::unique_ptr<node>;
  struct node {
    S val;
    node_ptr left, right;
    node() : val(), left(nullptr), right(nullptr) {}
    void update() {
      val = M::op(left ? left->val : M::e(), right ? right->val : M::e());
    }
  };
  size_t n;
  node_ptr root;

  void set(node_ptr& t, size_t a, size_t b, size_t& i, S& x) const {
    if (!t) t = std::make_unique<node>();
    if (b - a == 1) {
      t->val = x;
      return;
    }

    size_t c = (a + b) >> 1;
    if (i < c) set(t->left, a, c, i, x);
    else set(t->right, c, b, i, x);
    t->update();
  }

  S get(const node_ptr& t, size_t a, size_t b, size_t i) const {
    if (!t) return M::e();
    if (b - a == 1) {
      return t->val;
    }
    size_t c = (a + b) >> 1;
    if (i < c) return get(t->left, a, c, i);
    else return get(t->right, c, b, i);
  }

  S prod(const node_ptr& t, size_t a, size_t b, size_t l, size_t r) const {
    if (!t || b <= l || r <= a) return M::e();
    if (l <= a && b <= r) return t->val;
    size_t c = (a + b) >> 1;
    return M::op(prod(t->left, a, c, l, r), prod(t->right, c, b, l, r));
  }

  template <class F> size_t max_right(const node_ptr& t, size_t a, size_t b, S& product, size_t l, const F& f) const {
    if (!t || b <= l) return b;
    if (l <= a && f(M::op(product, t->val))) {
      product = M::op(product, t->val);
      return b;
    }
    if (b - a == 1) return a;
    size_t c = (a + b) >> 1;
    size_t test = max_right(t->left, a, c, product, l, f);
    return test < c ? test : max_right(t->right, c, b, product, l, f);
  }

  template <class F> size_t min_left(const node_ptr& t, size_t a, size_t b, S& product, size_t r, const F& f) {
    if (!t || r <= a) return a;
    if (b <= r && f(M::op(t->val, product))) {
      product = M::op(t->val, product);
      return a;
    }
    if (b - a == 1) return b;
    size_t c = (a + b) >> 1;
    size_t test = min_left(t->right, c, b, product, r, f);
    return test > c ? test : min_left(t->left, a, c, product, r, f);
  }
};
