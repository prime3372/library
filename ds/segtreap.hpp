#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "algebra/monoid.hpp"
#include "ds/implicit_treap_base.hpp"
#include "random/rng.hpp"

namespace cp {

template <monoid M> struct segtreap_node {
  using S = typename M::S;
  S val, prod;
  int sub = 1;
  bool rev = false;
  std::shared_ptr<segtreap_node> left, right;
  unsigned long long priority;

  segtreap_node() = default;
  explicit segtreap_node(const S& x) : val(x), prod(x), priority(mt64()) {}    
};

template <monoid M, auto flip = std::identity()>
struct segtreap
: public implicit_treap_base<segtreap_node<M>, segtreap<M, flip>> {
private:
  using S = typename M::S;
  using node = segtreap_node<M>;
  using node_ptr = std::shared_ptr<node>;
  using base = implicit_treap_base<node, segtreap<M, flip>>;
  using base::merge;
  using base::split;
  using base::size;
  using base::root;

public:
  using base::implicit_treap_base;

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return M::e();
    auto s = split(root, l);
    auto t = split(s.second, r - l);
    auto res = t.first->prod;
    root = merge(s.first, merge(t.first, t.second));
    return res;
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
  }
};

} // namespace cp