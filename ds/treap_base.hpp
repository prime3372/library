#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "ds/cartesian_tree.hpp"
#include "util/io_utility.hpp"

namespace cp {

template <class node, class derived> struct treap_base {
private:
  using T = decltype(node::val);
  using node_ptr = std::shared_ptr<node>;

public:
  treap_base() : root(nullptr) {}
  explicit treap_base(int n) : treap_base(std::vector<T>(n)) {}
  explicit treap_base(const std::vector<T>& v) {
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
    auto dfs = [](auto self, node_ptr p) -> void {
      if (p->left) self(self, p->left);
      if (p->right) self(self, p->right);
      update(p);
    };
    dfs(dfs, root = ps[cart.root]);  
  }

  void set(int k, const T& x) {
    assert(0 <= k && k < size());
    erase(k);
    insert(k, x);
  }

  const T& operator[](int k) const {
    assert(0 <= k && k < size());
    return get(root, k)->val;
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

  // for debugging
  friend std::ostream& operator<<(std::ostream& os, const treap_base& tp) {
    for (int i = 0; i < tp.size(); i++) {
      os << tp[i];
      if (i != tp.size() - 1) {
        internal::output_delimiter<T>(os);
      }
    }
    return os;
  }

protected:
  node_ptr root;

  static node_ptr merge(node_ptr left, node_ptr right) {
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

  static std::pair<node_ptr, node_ptr> split(node_ptr p, int k) {
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

  static node_ptr get(node_ptr p, int k) {
    push(p);
    if (size(p->left) == k) return p;
    if (k < size(p->left)) return get(p->left, k);
    else return get(p->right, k - size(p->left) - 1);
  }

  static int size(node_ptr p) { return p ? p->sub : 0; }

private:
  static void toggle(node_ptr p) { derived::toggle(p); }
  static void update(node_ptr p) { derived::update(p); }
  static void push(node_ptr p) { derived::push(p); }
};

} // namespace cp