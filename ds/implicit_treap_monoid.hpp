#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <utility>

#include "ds/implicit_treap_base.hpp"
#include "random/base.hpp"

namespace cp {

template <class S> struct implicit_treap_monoid_node {
  using self = implicit_treap_monoid_node;
  S val, prod;
  int sub = 1;
  bool rev = false;
  unsigned long long priority;
  self* left = nullptr;
  self* right = nullptr;

  implicit_treap_monoid_node() {}
  explicit implicit_treap_monoid_node(const S& x)
      : val(x), prod(x), priority(mt64()) {}
  implicit_treap_monoid_node(const self& other)
      : val(other.val),
        prod(other.prod),
        sub(other.sub),
        rev(other.rev),
        priority(other.priority),
        left(other.left ? new self(*other.left) : nullptr),
        right(other.right ? new self(*other.right) : nullptr) {}
  self& operator=(const self&) = delete;
  ~implicit_treap_monoid_node() {
    delete left;
    delete right;
  }
};

template <class S, auto op, auto e, auto reverse = std::identity()>
class implicit_treap_monoid
    : public implicit_treap_base<implicit_treap_monoid_node<S>,
                                 implicit_treap_monoid<S, op, e, reverse>> {
 public:
  implicit_treap_monoid() {}
  explicit implicit_treap_monoid(int n, const S& val = e())
      : implicit_treap_monoid(std::vector<S>(n, val)) {}
  explicit implicit_treap_monoid(const std::vector<S>& v) : base(v) {}

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return e();
    auto s1 = split(root, l);
    auto s2 = split(s1.second, r - l);
    auto res = s2.first->prod;
    root = merge(s1.first, merge(s2.first, s2.second));
    return res;
  }

 private:
  using node = implicit_treap_monoid_node<S>;
  using base = implicit_treap_base<node, implicit_treap_monoid>;
  friend base;
  using base::merge;
  using base::root;
  using base::size;
  using base::split;

  static void toggle(node* t) {
    std::swap(t->left, t->right);
    t->prod = reverse(t->prod);
    t->rev = !t->rev;
  }

  static void update(node* t) {
    t->sub = size(t->left) + size(t->right) + 1;
    t->prod = t->val;
    if (t->left) t->prod = op(t->left->prod, t->prod);
    if (t->right) t->prod = op(t->prod, t->right->prod);
  }

  static void push(node* t) {
    if (t->rev) {
      if (t->left) toggle(t->left);
      if (t->right) toggle(t->right);
      t->rev = false;
    }
  }
};

}  // namespace cp