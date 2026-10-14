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
struct ImplicitTreap : public ImplicitTreapBase<ImplicitTreapNode<T>> {
 public:
  ImplicitTreap() {}
  explicit ImplicitTreap(int n, const T& val = T{})
      : ImplicitTreap(std::vector<T>(n, val)) {}
  explicit ImplicitTreap(const std::vector<T>& v) { build(v); }

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