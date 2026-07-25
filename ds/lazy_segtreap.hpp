#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "algebra/acted_monoid.hpp"
#include "ds/treap_base.hpp"
#include "random/rng.hpp"

namespace cp {

template <acted_monoid M> struct lazy_segtreap_node {
public:
  using S = typename M::S;
  using F = typename M::F;
  S val, prod;
  F lz = M::id();
  int sub = 1;
  bool rev = false;
  std::shared_ptr<lazy_segtreap_node> left, right;
  unsigned long long priority;

  lazy_segtreap_node() = default;
  explicit lazy_segtreap_node(const S& x) : val(x), prod(x), priority(mt64()) {}  
};

template <acted_monoid M, auto flip = std::identity()>
struct lazy_segtreap
: public treap_base<lazy_segtreap_node<M>, lazy_segtreap<M, flip>> {
private:
  using S = typename M::S;
  using F = typename M::F;
  using node = lazy_segtreap_node<M>;
  using node_ptr = std::shared_ptr<node>;
  using base = treap_base<node, lazy_segtreap<M, flip>>;
  using base::merge;
  using base::split;
  using base::size;
  using base::root;

public:
  using base::treap_base;

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return M::e();
    auto s = split(root, l);
    auto t = split(s.second, r - l);
    auto res = t.first->prod;
    root = merge(s.first, merge(t.first, t.second));
    return res;
  }

  void apply(int l, int r, const F& f) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return;
    auto s = split(root, l);
    auto t = split(s.second, r - l);
    all_apply(t.first, f);
    root = merge(s.first, merge(t.first, t.second));
  }

private:
  friend base;

  static void toggle(node_ptr p) {
    swap(p->left, p->right);
    p->prod = flip(p->prod);
    p->rev = !p->rev;
  }

  static void update(node_ptr p) {
    push(p);
    p->sub = 1;
    p->prod = p->val;
    if (p->left) {
      p->sub += p->left->sub;
      p->prod = M::op(p->left->prod, p->prod);
    }
    if (p->right) {
      p->sub += p->right->sub;
      p->prod = M::op(p->prod, p->right->prod);
    }
  }

  static void push(node_ptr p) {
    if (p->rev) {
      if (p->left) toggle(p->left);
      if (p->right) toggle(p->right);
      p->rev = false;
    }
    if (p->left) all_apply(p->left, p->lz);
    if (p->right) all_apply(p->right, p->lz);
    p->lz = M::id();
  }

  static void all_apply(node_ptr p, const F& f) {
    p->lz = M::composition(f, p->lz);
    p->val = M::composition(f, p->val);
    p->prod = M::mapping(f, p->prod);
  }
};

} // namespace cp