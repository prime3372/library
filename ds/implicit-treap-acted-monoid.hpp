#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "ds/implicit-treap-base.hpp"
#include "random/engine.hpp"

namespace cp {

template <class S, class F, auto id> struct ImplicitTreapActedMonoidNode {
  using Self = ImplicitTreapActedMonoidNode;
  S val, prod;
  F lz = id();
  Self* left = nullptr;
  Self* right = nullptr;
  int sub = 1;
  unsigned long long priority;
  bool rev = false;
  bool lzflag = false;
  ImplicitTreapActedMonoidNode(const S& x) : val(x), prod(x), priority(rng()) {}
};

template <class S,
          auto op,
          auto e,
          class F,
          auto act,
          auto compose,
          auto id,
          auto reverse = std::identity{}>
class ImplicitTreapActedMonoid
    : public ImplicitTreapBase<ImplicitTreapActedMonoidNode<S, F, id>> {
 public:
  ImplicitTreapActedMonoid() {}
  explicit ImplicitTreapActedMonoid(int n, const S& val = e())
      : ImplicitTreapActedMonoid(std::vector<S>(n, val)) {}
  explicit ImplicitTreapActedMonoid(const std::vector<S>& v) { build(v); }

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

 private:
  using Node = ImplicitTreapActedMonoidNode<S, F, id>;
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
    if (t->lzflag) {
      if (t->left) all_apply(t->left, t->lz);
      if (t->right) all_apply(t->right, t->lz);
      t->lz = id();
      t->lzflag = false;
    }
  }

  void all_apply(Node* t, const F& f) {
    t->lz = compose(f, t->lz);
    t->val = act(f, t->val);
    t->prod = act(f, t->prod);
    t->lzflag = true;
  }
};

}  // namespace cp