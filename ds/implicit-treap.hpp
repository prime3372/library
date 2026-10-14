#pragma once

#include <cassert>
#include <functional>
#include <vector>

#include "ds/implicit-treap-base.hpp"
#include "random/engine.hpp"

namespace cp {

template <class T> struct ImplicitTreapNode {
  using Self = ImplicitTreapNode;
  T val;
  int sub = 1;
  unsigned long long priority;
  Self* left = nullptr;
  Self* right = nullptr;
  bool rev = false;
  ImplicitTreapNode(const T& x) : val(x), priority(rng()) {}
};

template <class T>
struct implicit_treap : public ImplicitTreapBase<ImplicitTreapNode<T>> {
 public:
  implicit_treap() {}
  explicit implicit_treap(int n, const T& val = T{})
      : implicit_treap(std::vector<T>(n, val)) {}
  explicit implicit_treap(const std::vector<T>& v) { build(v); }

 private:
  using Node = ImplicitTreapNode<T>;
  using Base = ImplicitTreapBase<Node>;
  friend Base;
  using Base::build;
  using Base::root;
  using Base::size;

  void toggle(Node* t) override {
    std::swap(t->left, t->right);
    t->rev = !t->rev;
  }

  void update(Node* t) override { t->sub = size(t->left) + size(t->right) + 1; }

  void push(Node* t) override {
    if (t->rev) {
      if (t->left) toggle(t->left);
      if (t->right) toggle(t->right);
      t->rev = false;
    }
  }
};

}  // namespace cp