#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include "ds/cartesian_tree.hpp"
#include "util/io_utility.hpp"

namespace cp {

namespace internal {

template <class node> struct treap_base {
public:
  using T = decltype(node::val);
  using node_ptr = std::shared_ptr<node>;

  treap_base() {}

  void build(const std::vector<T>& v) {
    if (v.empty()) return;
    int n = int(v.size());
    std::vector<node_ptr> ps(n);
    std::vector<unsigned long long> pr(n);
    for (int i = 0; i < n; i++) {
      ps[i] = std::make_shared<node>(v[i]);
      pr[i] = ps[i]->priority;
    }
    cartesian_tree<true> cart(pr);
    for (int i = 0; i < n; i++) {
      if (cart.left[i] != -1) {
        ps[i]->left = ps[cart.left[i]];
      }
      if (cart.right[i] != -1) {
        ps[i]->right = ps[cart.right[i]];
      }
    }
    auto dfs = [&](auto self, node_ptr p) -> void {
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
    root = merge(merge(s.first, std::make_shared<node>(x)), s.second);
  }

  void erase(int k) {
    assert(0 <= k && k < size());
    auto s = split(root, k);
    root = merge(s.first, split(s.second, 1).second);
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

  friend std::ostream& operator<<(std::ostream& os, const treap_base& tp) {
    for (int i = 0; i < tp.size(); i++) {
      os << tp[i];
      if (i != tp.size() - 1) {
        os << internal::delimiter_of_v<T>;
      }
    }
    return os;
  }

protected:
  node_ptr root;

  node_ptr& merge(node_ptr& left, node_ptr& right) {
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

  std::pair<node_ptr, node_ptr> split(node_ptr p, int k) {
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

  int size(node_ptr p) const { return p ? p->sub : 0; }

  virtual void toggle(node_ptr p) = 0;

  virtual void update(node_ptr p) = 0;

  virtual void push(node_ptr p) = 0;
};

} // namespace internal

} // namespace cp