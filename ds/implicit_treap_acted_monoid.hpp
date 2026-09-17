#pragma once

#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>

#include "ds/implicit_treap_base.hpp"
#include "random/engine.hpp"
#include "util/io_utility.hpp"

namespace cp {

template <class S, class F, auto id> struct implicit_treap_acted_monoid_node {
  using self = implicit_treap_acted_monoid_node;
  S val, prod;
  F lz = id();
  self* left = nullptr;
  self* right = nullptr;
  int sub = 1;
  unsigned long long priority;
  bool rev = false;
  bool lzflag = false;

  implicit_treap_acted_monoid_node() {}
  explicit implicit_treap_acted_monoid_node(const S& x)
      : val(x), prod(x), priority(xs64()) {}
};

template <class S, auto op, auto e, class F, auto act, auto compose, auto id,
          auto reverse = std::identity()>
class implicit_treap_acted_monoid
    : public implicit_treap_base<implicit_treap_acted_monoid_node<S, F, id>> {
 public:
  implicit_treap_acted_monoid() {}
  explicit implicit_treap_acted_monoid(int n, const S& val = e())
      : implicit_treap_acted_monoid(std::vector<S>(n, val)) {}
  explicit implicit_treap_acted_monoid(const std::vector<S>& v) { build(v); }

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return e();
    auto s1 = split(root, l);
    auto s2 = split(s1.second, r - l);
    S res = s2.first->prod;
    root = merge(s1.first, merge(s2.first, s2.second));
    return res;
  }

  void apply(int l, int r, const F& f) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return;
    auto s1 = split(root, l);
    auto s2 = split(s1.second, r - l);
    all_apply(s2.first, f);
    root = merge(s1.first, merge(s2.first, s2.second));
  }

  friend std::ostream& operator<<(std::ostream& os, implicit_treap_acted_monoid t) {
    std::vector<S> v(t.size());
    for (int i = 0; i < t.size(); i++) v[i] = t[i];
    return os << v;
  }

 private:
  using node = implicit_treap_acted_monoid_node<S, F, id>;
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
    if (t->lzflag) {
      if (t->left) all_apply(t->left, t->lz);
      if (t->right) all_apply(t->right, t->lz);
      t->lz = id();
      t->lzflag = false;
    }
  }

  void all_apply(node* t, const F& f) {
    t->lz = compose(f, t->lz);
    t->val = act(f, t->val);
    t->prod = act(f, t->prod);
    t->lzflag = true;
  }
};

}  // namespace cp