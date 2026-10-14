#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <utility>

#include "ds/implicit-treap-base.hpp"
#include "random/engine.hpp"

namespace cp {

template <class S> struct ImplicitTreapMonoidNode {
  using Self = ImplicitTreapMonoidNode;
  S val, prod;
  int sub = 1;
  unsigned long long priority;
  Self* left = nullptr;
  Self* right = nullptr;
  bool rev = false;
  ImplicitTreapMonoidNode(const S& x) : val(x), prod(x), priority(rng()) {}
};

template <class S, auto op, auto e, auto reverse = std::identity{}>
struct ImplicitTreapMonoid
    : public ImplicitTreapBase<ImplicitTreapMonoidNode<S>> {
 public:
  ImplicitTreapMonoid() {}
  explicit ImplicitTreapMonoid(int n, const S& val = e())
      : ImplicitTreapMonoid(std::vector<S>(n, val)) {}
  explicit ImplicitTreapMonoid(const std::vector<S>& v) { build(v); }

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
  using Node = ImplicitTreapMonoidNode<S>;
  using Base = ImplicitTreapBase<Node>;
  friend Base;
  using Base::build;
  using Base::merge;
  using Base::root;
  using Base::size;
  using Base::split;

  void toggle(Node* t) override {
    std::swap(t->left, t->right);
    t->prod = reverse(t->prod);
    t->rev = !t->rev;
  }

  void update(Node* t) override {
    t->sub = size(t->left) + size(t->right) + 1;
    t->prod = t->val;
    if (t->left) t->prod = op(t->left->prod, t->prod);
    if (t->right) t->prod = op(t->prod, t->right->prod);
  }

  void push(Node* t) override {
    if (t->rev) {
      if (t->left) toggle(t->left);
      if (t->right) toggle(t->right);
      t->rev = false;
    }
  }
};

}  // namespace cp