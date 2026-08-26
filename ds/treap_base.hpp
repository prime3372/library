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

template <class node, class derived> class treap_base {
  using T = decltype(node::val);

 public:
  treap_base() {}
  explicit treap_base(int n) : treap_base(std::vector<T>(n)) {}
  explicit treap_base(int n, const T& val) : treap_base(std::vector<T>(n, val)) {}
  explicit treap_base(const std::vector<T>& v) { build(v); }

  ~treap_base() { delete root; }

  // @warning Coping can have side effects on the original.
  treap_base(treap_base& other) {
    if (!other.root) return;
    std::vector<T> data(other.size());
    auto dfs = [&](auto self, node* p, int k) -> void {
      if (!p) return;
      derived::push(p);
      self(self, p->left, k);
      self(self, p->right, k + size(p->left) + 1);
      derived::update(p);
      data[k + size(p->left)] = p->val;
    };
    dfs(dfs, other.root, 0);
    build(data);
  }
  treap_base(treap_base&& other) : root(other.root) { other.root = nullptr; }
  treap_base& operator=(treap_base other) {
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
    cartesian_tree<true> cart(pr);
    for (int i = 0; i < n; i++) {
      if (cart.left[i] != -1) ps[i]->left = ps[cart.left[i]];
      if (cart.right[i] != -1) ps[i]->right = ps[cart.right[i]];
    }
    auto dfs = [&](auto self, node* p) -> void {
      if (!p) return;
      self(self, p->left);
      self(self, p->right);
      derived::update(p);
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
    auto s = split(root, k);
    auto t = split(s.second, 1);
    delete t.first;
    root = merge(s.first, t.second);
  }

  void reverse(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return;
    auto s = split(root, l);
    auto t = split(s.second, r - l);
    derived::toggle(t.first);
    root = merge(s.first, merge(t.first, t.second));
  }

  int size() const { return size(root); }

  friend std::ostream& operator<<(std::ostream& os, derived tp) {
    std::vector<std::string> outs(tp.size());
    std::ostringstream oss;
    for (int i = 0; i < int(outs.size()); i++) {
      oss << tp[i];
      outs[i] = oss.str();
      oss.str("");
    }
    return os << internal::combine_outputs(outs);
  }

 protected:
  node* root = nullptr;

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

  static std::pair<node*, node*> split(node* p, int k) {
    if (!p) return {nullptr, nullptr};
    derived::push(p);
    if (k <= size(p->left)) {
      auto s = split(p->left, k);
      p->left = s.second;
      derived::update(p);
      return {s.first, p};
    } else {
      auto s = split(p->right, k - size(p->left) - 1);
      p->right = s.first;
      derived::update(p);
      return {p, s.second};
    }
  }

  static int size(const node* p) { return p ? p->sub : 0; }
};

}  // namespace cp