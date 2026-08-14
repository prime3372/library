#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "ds/treap_base.hpp"
#include "random/base.hpp"

namespace cp {

namespace internal {

template <class T> struct treap_node {
  T val;
  int sub = 1;
  bool rev = false;
  treap_node* left = nullptr;
  treap_node* right = nullptr;
  unsigned long long priority;

  treap_node() {};
  explicit treap_node(const T& x) : val(x), priority(mt64()) {}    
};

} // namespace internal

template <class T>
struct treap : public internal::treap_base<internal::treap_node<T>> {
public:
  using node = internal::treap_node<T>;
  using node_ptr = std::shared_ptr<node>;
  using base = internal::treap_base<node>;

  treap() {}
  explicit treap(int n) { build(std::vector<T>(n)); }
  explicit treap(int n, const T& val) { build(std::vector<T>(n, val)); }
  explicit treap(const std::vector<T>& v) { build(v); }

protected:
  using base::build;

  void toggle(node* p) override {
    std::swap(p->left, p->right);
    p->rev = !p->rev;
  }

  void update(node* p) override {
    p->sub = 1;
    if (p->left) p->sub += p->left->sub;
    if (p->right) p->sub += p->right->sub;
  }

  void push(node* p) override {
    if (p->rev) {
      if (p->left) toggle(p->left);
      if (p->right) toggle(p->right);
      p->rev = false;
    }
  }
};

} // namespace cp