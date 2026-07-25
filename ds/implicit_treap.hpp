#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "ds/implicit_treap_base.hpp"
#include "random/rng.hpp"

namespace cp {

template <class T> struct implicit_treap_node {
  T val;
  int sub = 1;
  bool rev = false;
  std::shared_ptr<implicit_treap_node> left, right;
  unsigned long long priority;

  implicit_treap_node() = default;
  explicit implicit_treap_node(const T& x) : val(x), priority(mt64()) {}    
};

template <class T> struct implicit_treap
: public implicit_treap_base<implicit_treap_node<T>, implicit_treap<T>> {
private:
  using node = implicit_treap_node<T>;
  using node_ptr = std::shared_ptr<node>;
  using base = implicit_treap_base<node, implicit_treap>;

public:
  using base::implicit_treap_base;

private:
  friend base;

  static void toggle(node_ptr p) {
    swap(p->left, p->right);
    p->rev = !p->rev;
  }

  static void update(node_ptr p) {
    push(p);
    p->sub = 1;
    if (p->left) p->sub += p->left->sub;
    if (p->right) p->sub += p->right->sub;
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