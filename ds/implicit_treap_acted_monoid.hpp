#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "ds/implicit_treap_base.hpp"
#include "random/base.hpp"

namespace cp {

template <class S, class F, auto id> struct implicit_treap_acted_monoid_node {
  using self = implicit_treap_acted_monoid_node;
  S val, prod;
  F lz = id();
  int sub = 1;
  bool rev = false;
  unsigned long long priority;
  self* left = nullptr;
  self* right = nullptr;

  implicit_treap_acted_monoid_node() {}
  explicit implicit_treap_acted_monoid_node(const S& x)
      : val(x), prod(x), priority(mt64()) {}
  implicit_treap_acted_monoid_node(const self& other)
      : val(other.val),
        prod(other.prod),
        lz(other.lz),
        sub(other.sub),
        rev(other.rev),
        priority(other.priority),
        left(other.left ? new self(*other.left) : nullptr),
        right(other.right ? new self(*other.right) : nullptr) {}
  self& operator=(const self&) = delete;
  ~implicit_treap_acted_monoid_node() {
    delete left;
    delete right;
  }
};

template <class S, auto op, auto e, class F, auto act, auto compose, auto id,
          auto reverse = std::identity()>
class implicit_treap_acted_monoid
    : public implicit_treap_base<
          implicit_treap_acted_monoid_node<S, F, id>,
          implicit_treap_acted_monoid<S, op, e, F, act, compose, id, reverse>> {
 public:
  implicit_treap_acted_monoid() {}
  explicit implicit_treap_acted_monoid(int n, const S& val = e())
      : implicit_treap_acted_monoid(std::vector<S>(n, val)) {}
  explicit implicit_treap_acted_monoid(const std::vector<S>& v) { build(v); }

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return e();
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
  using node = implicit_treap_acted_monoid_node<S, F, id>;
  using base = implicit_treap_base<node, implicit_treap_acted_monoid>;
  friend base;
  using base::build;
  using base::merge;
  using base::root;
  using base::size;
  using base::split;

  static void toggle(node* p) {
    std::swap(p->left, p->right);
    p->prod = reverse(p->prod);
    p->rev = !p->rev;
  }

  static void update(node* p) {
    p->sub = 1;
    p->prod = p->val;
    if (p->left) {
      p->sub += p->left->sub;
      p->prod = op(p->left->prod, p->prod);
    }
    if (p->right) {
      p->sub += p->right->sub;
      p->prod = op(p->prod, p->right->prod);
    }
  }

  static void push(node* p) {
    if (p->rev) {
      if (p->left) toggle(p->left);
      if (p->right) toggle(p->right);
      p->rev = false;
    }
    if (p->left) all_apply(p->left, p->lz);
    if (p->right) all_apply(p->right, p->lz);
    p->lz = id();
  }

  static void all_apply(node* p, F f) {
    p->lz = compose(f, p->lz);
    p->val = act(f, p->val);
    p->prod = act(f, p->prod);
  }
};

}  // namespace cp