#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "ds/treap_base.hpp"
#include "random/common.hpp"

namespace cp {

template <class T> struct treap_node {
  T val;
  int sub = 1;
  bool rev = false;
  std::shared_ptr<treap_node> left, right;
  unsigned long long priority;

  treap_node() {};
  explicit treap_node(const T& x) : val(x), priority(mt64()) {}    
};

template <class T> struct treap : public treap_base<treap_node<T>> {
public:
  using node = treap_node<T>;
  using node_ptr = std::shared_ptr<node>;
  using base = treap_base<node>;

  treap() {}
  explicit treap(int n) { build(std::vector<T>(n)); }
  explicit treap(int n, const T& val) { build(std::vector<T>(n, val)); }
  explicit treap(const std::vector<T>& v) { build(v); }

protected:
  using base::build;

  void toggle(node_ptr p) const override {
    swap(p->left, p->right);
    p->rev = !p->rev;
  }

  void update(node_ptr p) const override {
    push(p);
    p->sub = 1;
    if (p->left) p->sub += p->left->sub;
    if (p->right) p->sub += p->right->sub;
  }

  void push(node_ptr p) const override {
    if (p->rev) {
      if (p->left) toggle(p->left);
      if (p->right) toggle(p->right);
      p->rev = false;
    }
  }
};

} // namespace cp