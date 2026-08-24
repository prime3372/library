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

template <class node> class treap_base {
  using T = decltype(node::val);

 public:
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
      if (p->left) self(self, p->left);
      if (p->right) self(self, p->right);
      update(p);
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
    toggle(t.first);
    root = merge(s.first, merge(t.first, t.second));
  }

  int size() const { return size(root); }

  friend std::ostream& operator<<(std::ostream& os, treap_base tp) {
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

  treap_base() {}
  ~treap_base() { delete root; }

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

  std::pair<node*, node*> split(node* p, int k) {
    if (!p) return {nullptr, nullptr};
    push(p);
    if (k <= size(p->left)) {
      auto s = split(p->left, k);
      p->left = s.second;
      update(p);
      return {s.first, p};
    } else {
      auto s = split(p->right, k - size(p->left) - 1);
      p->right = s.first;
      update(p);
      return {p, s.second};
    }
  }

  int size(const node* p) const { return p ? p->sub : 0; }

  virtual void toggle(node* p) = 0;
  virtual void update(node* p) = 0;
  virtual void push(node* p) = 0;
};

}  // namespace cp