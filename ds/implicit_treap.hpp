#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "ds/implicit_treap_base.hpp"
#include "random/base.hpp"

namespace cp {

template <class T> struct implicit_treap_node {
  using self = implicit_treap_node;
  T val;
  int sub = 1;
  bool rev = false;
  unsigned long long priority;
  self* left = nullptr;
  self* right = nullptr;

  implicit_treap_node() {}
  explicit implicit_treap_node(const T& x) : val(x), priority(mt64()) {}
  implicit_treap_node(const self& other)
      : val(other.val),
        sub(other.sub),
        rev(other.rev),
        priority(other.priority),
        left(other.left ? new self(*other.left) : nullptr),
        right(other.right ? new self(*other.right) : nullptr) {}
  self& operator=(const self&) = delete;
  ~implicit_treap_node() {
    delete left;
    delete right;
  }
};

template <class T>
class implicit_treap
    : public implicit_treap_base<implicit_treap_node<T>, implicit_treap<T>> {
  using node = implicit_treap_node<T>;
  using base = implicit_treap_base<node, implicit_treap>;

 public:
  using base::base;

 private:
  friend base;

  static void toggle(node* p) {
    std::swap(p->left, p->right);
    p->rev = !p->rev;
  }

  static void update(node* p) {
    p->sub = 1;
    if (p->left) p->sub += p->left->sub;
    if (p->right) p->sub += p->right->sub;
  }

  static void push(node* p) {
    if (p->rev) {
      if (p->left) toggle(p->left);
      if (p->right) toggle(p->right);
      p->rev = false;
    }
  }
};

}  // namespace cp