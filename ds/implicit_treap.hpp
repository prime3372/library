#pragma once

#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>

#include "ds/implicit_treap_base.hpp"
#include "random/engine.hpp"
#include "util/memory_pool.hpp"

namespace cp {

template <class T> struct implicit_treap_node {
  using self = implicit_treap_node;
  inline static memory_pool<implicit_treap_node> pool;

  T val;
  int sub = 1;
  bool rev = false;
  unsigned long long priority;
  self* left = nullptr;
  self* right = nullptr;

  implicit_treap_node() {}
  explicit implicit_treap_node(const T& x) : val(x), priority(xs64()) {}
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
  void* operator new(std::size_t) { return pool.malloc(); }
  void operator delete(void* ptr) { return pool.free((self*)(ptr)); }
};

template <class T>
class implicit_treap
    : public implicit_treap_base<implicit_treap_node<T>, implicit_treap<T>> {
 public:
  implicit_treap() {}
  explicit implicit_treap(int n, const T& val = T())
      : implicit_treap(std::vector<T>(n, val)) {}
  explicit implicit_treap(const std::vector<T>& v) : base(v) {}

 private:
  using node = implicit_treap_node<T>;
  using base = implicit_treap_base<node, implicit_treap>;
  friend base;
  using base::size;

  static void toggle(node* t) {
    std::swap(t->left, t->right);
    t->rev = !t->rev;
  }

  static void update(node* t) { t->sub = size(t->left) + size(t->right) + 1; }

  static void push(node* t) {
    if (t->rev) {
      if (t->left) toggle(t->left);
      if (t->right) toggle(t->right);
      t->rev = false;
    }
  }
};

}  // namespace cp