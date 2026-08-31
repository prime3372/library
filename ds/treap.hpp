#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "ds/treap_base.hpp"
#include "random/base.hpp"

namespace cp {

template <class T> struct treap_node {
  T val;
  int sub = 1;
  bool rev = false;
  unsigned long long priority;
  treap_node* left = nullptr;
  treap_node* right = nullptr;

  treap_node() {}
  explicit treap_node(const T& x) : val(x), priority(mt64()) {}
  treap_node(const treap_node& other)
      : val(other.val),
        sub(other.sub),
        rev(other.rev),
        priority(other.priority),
        left(other.left ? new treap_node(*other.left) : nullptr),
        right(other.right ? new treap_node(*other.right) : nullptr) {}
  treap_node& operator=(const treap_node&) = delete;
  ~treap_node() {
    delete left;
    delete right;
  }
};

template <class T>
class treap : public treap_base<treap_node<T>, treap<T>> {
  using node = treap_node<T>;
  using base = treap_base<node, treap>;

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