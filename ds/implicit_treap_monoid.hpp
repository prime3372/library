#pragma once

#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>
#include <utility>

#include "ds/implicit_treap_base.hpp"
#include "random/engine.hpp"
#include "util/io_utility.hpp"

namespace cp {

template <class S> struct implicit_treap_monoid_node {
  using self = implicit_treap_monoid_node;
  S val, prod;
  int sub = 1;
  unsigned long long priority;
  self* left = nullptr;
  self* right = nullptr;
  bool rev = false;

  implicit_treap_monoid_node(const S& x) : val(x), prod(x), priority(rng()) {}
};

template <class S, auto op, auto e, auto reverse = std::identity()>
class implicit_treap_monoid
    : public implicit_treap_base<implicit_treap_monoid_node<S>> {
 public:
  implicit_treap_monoid() {}
  explicit implicit_treap_monoid(int n, const S& val = e())
      : implicit_treap_monoid(std::vector<S>(n, val)) {}
  explicit implicit_treap_monoid(const std::vector<S>& v) { build(v); }

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return e();
    auto s1 = split(root, l);
    auto s2 = split(s1.second, r - l);
    auto res = s2.first->prod;
    root = merge(s1.first, merge(s2.first, s2.second));
    return res;
  }

  friend std::ostream& operator<<(std::ostream& os, implicit_treap_monoid t) {
    std::vector<S> v(t.size());
    for (int i = 0; i < t.size(); i++) v[i] = t[i];
    return os << v;
  }

 private:
  using node = implicit_treap_monoid_node<S>;
  using base = implicit_treap_base<node>;
  friend base;
  using base::build;
  using base::merge;
  using base::root;
  using base::size;
  using base::split;

  void toggle(node* t) override {
    std::swap(t->left, t->right);
    t->prod = reverse(t->prod);
    t->rev = !t->rev;
  }

  void update(node* t) override {
    t->sub = size(t->left) + size(t->right) + 1;
    t->prod = t->val;
    if (t->left) t->prod = op(t->left->prod, t->prod);
    if (t->right) t->prod = op(t->prod, t->right->prod);
  }

  void push(node* t) override {
    if (t->rev) {
      if (t->left) toggle(t->left);
      if (t->right) toggle(t->right);
      t->rev = false;
    }
  }
};

}  // namespace cp