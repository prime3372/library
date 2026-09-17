#pragma once

#include <cassert>
#include <cstddef>
#include <functional>
#include <vector>

#include "ds/implicit_treap_base.hpp"
#include "random/engine.hpp"

namespace cp {

template <class T> struct implicit_treap_node {
  using self = implicit_treap_node;
  T val;
  int sub = 1;
  unsigned long long priority;
  self* left = nullptr;
  self* right = nullptr;
  bool rev = false;

  implicit_treap_node() {}
  explicit implicit_treap_node(const T& x) : val(x), priority(xs64()) {}
};

template <class T>
class implicit_treap : public implicit_treap_base<implicit_treap_node<T>> {
 public:
  implicit_treap() {}
  explicit implicit_treap(int n, const T& val = T())
      : implicit_treap(std::vector<T>(n, val)) {}
  explicit implicit_treap(const std::vector<T>& v) { build(v); }

  friend std::ostream& operator<<(std::ostream& os, implicit_treap tp) {
    std::vector<T> v(tp.size());
    for (int i = 0; i < tp.size(); i++) v[i] = tp[i];
    return os << v;
  }

 private:
  using node = implicit_treap_node<T>;
  using base = implicit_treap_base<node>;
  friend base;
  using base::build;
  using base::size;

  void toggle(node* t) override {
    std::swap(t->left, t->right);
    t->rev = !t->rev;
  }

  void update(node* t) override { t->sub = size(t->left) + size(t->right) + 1; }

  void push(node* t) override {
    if (t->rev) {
      if (t->left) toggle(t->left);
      if (t->right) toggle(t->right);
      t->rev = false;
    }
  }
};

}  // namespace cp