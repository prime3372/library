#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "ds/cartesian_tree.hpp"
#include "util/io_utility_base.hpp"

namespace cp {

template <class node, class derived> class implicit_treap_base {
  using T = decltype(node::val);

 public:
  implicit_treap_base() {}
  implicit_treap_base(const implicit_treap_base& other)
      : root(other.root ? new node(*other.root) : nullptr) {}
  implicit_treap_base(implicit_treap_base&& other) noexcept : root(other.root) {
    other.root = nullptr;
  }
  implicit_treap_base& operator=(implicit_treap_base other) {
    std::swap(root, other.root);
    return *this;
  }
  ~implicit_treap_base() { delete root; }

  void build(const std::vector<T>& v) {
    if (v.empty()) return;
    int n = int(v.size());
    std::vector<node*> ps(n);
    std::vector<unsigned long long> pr(n);
    for (int i = 0; i < n; i++) {
      ps[i] = new node(v[i]);
      pr[i] = ps[i]->priority;
    }
    cartesian_tree cart(pr, std::greater<unsigned long long>());
    for (int i = 0; i < n; i++) {
      if (cart.left[i] != -1) ps[i]->left = ps[cart.left[i]];
      if (cart.right[i] != -1) ps[i]->right = ps[cart.right[i]];
    }
    auto dfs = [&](auto self, node* t) -> void {
      if (!t) return;
      self(self, t->left);
      self(self, t->right);
      derived::update(t);
    };
    dfs(dfs, root = ps[cart.root]);
  }

  void set(int k, const T& x) {
    assert(0 <= k && k < size());
    auto s1 = split(root, k);
    auto s2 = split(s1.second, 1);
    s2.first->val = x;
    root = merge(s1.first, merge(s2.first, s2.second));
  }

  const T& operator[](int k) {
    assert(0 <= k && k < size());
    auto s1 = split(root, k);
    auto s2 = split(s1.second, 1);
    const T& res = s2.first->val;
    root = merge(s1.first, merge(s2.first, s2.second));
    return res;
  }

  void insert(int k, const T& x) {
    assert(0 <= k && k <= size());
    auto s = split(root, k);
    root = merge(merge(s.first, new node(x)), s.second);
  }

  void erase(int k) {
    assert(0 <= k && k < size());
    auto s1 = split(root, k);
    auto s2 = split(s1.second, 1);
    delete s2.first;
    root = merge(s1.first, s2.second);
  }

  void reverse(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return;
    auto s1 = split(root, l);
    auto s2 = split(s1.second, r - l);
    derived::toggle(s2.first);
    root = merge(s1.first, merge(s2.first, s2.second));
  }

  int size() const { return size(root); }
  bool empty() const { return size() == 0; }

  friend std::ostream& operator<<(std::ostream& os, derived tp) {
    using io_utility::operator<<;
    std::vector<T> v(tp.size());
    for (int i = 0; i < tp.size(); i++) v[i] = tp[i];
    return os << v;
  }

 protected:
  node* root = nullptr;

  static int size(const node* t) { return t ? t->sub : 0; }

  static std::pair<node*, node*> split(node* t, int k) {
    if (!t) return {nullptr, nullptr};
    derived::push(t);
    if (k <= size(t->left)) {
      auto s = split(t->left, k);
      t->left = s.second;
      derived::update(t);
      return {s.first, t};
    } else {
      auto s = split(t->right, k - size(t->left) - 1);
      t->right = s.first;
      derived::update(t);
      return {t, s.second};
    }
  }

  static node* merge(node* left, node* right) {
    if (!left || !right) return left ? left : right;
    if (left->priority > right->priority) {
      derived::push(left);
      left->right = merge(left->right, right);
      derived::update(left);
      return left;
    } else {
      derived::push(right);
      right->left = merge(left, right->left);
      derived::update(right);
      return right;
    }
  }
};

}  // namespace cp