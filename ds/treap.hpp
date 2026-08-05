#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "ds/treap_base.hpp"
#include "random/get_rand.hpp"

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
private:
  using node = treap_node<T>;
  using node_ptr = std::shared_ptr<node>;
  using base = treap_base<node>;
  using base::build;

public:
  treap() {}
  explicit treap(int n) { build(std::vector<T>(n)); }
  explicit treap(int n, const T& val) { build(std::vector<T>(n, val)); }
  explicit treap(const std::vector<T>& v) { build(v); }

protected:
  void toggle(node_ptr p) override {
    swap(p->left, p->right);
    p->rev = !p->rev;
  }

  void update(node_ptr p) override {
    push(p);
    p->sub = 1;
    if (p->left) p->sub += p->left->sub;
    if (p->right) p->sub += p->right->sub;
  }

  void push(node_ptr p) override {
    if (p->rev) {
      if (p->left) toggle(p->left);
      if (p->right) toggle(p->right);
      p->rev = false;
    }
  }
};

} // namespace cp