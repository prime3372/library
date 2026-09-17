#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "ds/cartesian_tree.hpp"

namespace cp {

template <class node> class implicit_treap_base {
  using T = decltype(node::val);

 public:
  virtual ~implicit_treap_base() {
    auto dfs = [&](auto self, node* t) -> void {
      if (!t) return;
      self(self, t->left);
      self(self, t->right);
      delete t;
    };
    dfs(dfs, root);
  }

  void set(int k, const T& x) {
    assert(0 <= k && k < size());
    auto s1 = split(root, k);
    auto s2 = split(s1.second, 1);
    s2.first->val = x;
    update(s2.first);
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
  const T& front() {
    assert(!empty());
    return (*this)[0];
  }
  const T& back() {
    assert(!empty());
    return (*this)[size() - 1];
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
    toggle(s2.first);
    root = merge(s1.first, merge(s2.first, s2.second));
  }

  int size() const { return size(root); }
  bool empty() const { return size() == 0; }

 protected:
  node* root = nullptr;

  implicit_treap_base() {}
  implicit_treap_base(const implicit_treap_base& other) {
    auto dfs = [&](auto self, node* t) -> node* {
      if (!t) return nullptr;
      node* res = new node(*t);
      res->left = self(self, t->left);
      res->right = self(self, t->right);
      return res;
    };
    root = dfs(dfs, other.root);
  }
  implicit_treap_base(implicit_treap_base&& other) : root(other.root) {
    other.root = nullptr;
  }
  implicit_treap_base& operator=(implicit_treap_base other) {
    std::swap(root, other.root);
    return *this;
  }

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
      update(t);
    };
    dfs(dfs, root = ps[cart.root]);
  }

  int size(const node* t) const { return t ? t->sub : 0; }

  std::pair<node*, node*> split(node* t, int k) {
    if (!t) return {nullptr, nullptr};
    push(t);
    if (k <= size(t->left)) {
      auto s = split(t->left, k);
      t->left = s.second;
      update(t);
      return {s.first, t};
    } else {
      auto s = split(t->right, k - size(t->left) - 1);
      t->right = s.first;
      update(t);
      return {t, s.second};
    }
  }

  node* merge(node* left, node* right) {
    if (!left || !right) return left ? left : right;
    if (left->priority > right->priority) {
      push(left);
      left->right = merge(left->right, right);
      update(left);
      return left;
    } else {
      push(right);
      right->left = merge(left, right->left);
      update(right);
      return right;
    }
  }

  virtual void toggle(node*) = 0;
  virtual void update(node*) = 0;
  virtual void push(node*) = 0;
};

}  // namespace cp