#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

#include "ds/cartesian_tree.hpp"
#include "random/base.hpp"
#include "util/io_utility_base.hpp"

namespace cp {

template <class T, bool multiset, class Comp = std::less<T>> class treap {
 public:
  treap() {}
  explicit treap(std::vector<T> v) {
    if (v.empty()) return;
    int n = int(v.size());
    bool sorted = true, unique = true;
    for (int i = 0; i < n - 1; i++) {
      if (less(v[i + 1], v[i])) {
        sorted = false;
        break;
      }
      if (equal(v[i], v[i + 1])) unique = false;
    }
    if (!sorted) std::sort(v.begin(), v.end(), less);
    if (!multiset && (!sorted || !unique)) {
      v.erase(std::unique(v.begin(), v.end(), equal), v.end());
      n = int(v.size());
    }
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
  treap(const treap& other)
      : root(other.root ? new node(*other.root) : nullptr) {}
  treap(treap&& other) noexcept : root(other.root) { other.root = nullptr; }
  treap& operator=(treap other) {
    std::swap(root, other.root);
    return *this;
  }
  ~treap() { delete root; }

  bool insert(const T& k) {
    if (!multiset && contains(k)) return false;
    insert(root, new node(k));
    return true;
  }

  // @note If there are elements equivalent to x, select one of them and remove
  // it; otherwise, do nothing.
  bool erase(const T& k) { return erase(root, k); }

  const T& operator[](int i) const {
    assert(0 <= i && i < size());
    const node* t = root;
    while (size(t->left) != i) {
      if (i < size(t->left)) {
        t = t->left;
      } else {
        i -= size(t->left) + 1;
        t = t->right;
      }
    }
    return t->key;
  }

  int lower_bound(const T& k) const {
    return binary_search([&](const T& x) { return less(x, k); });
  }
  int upper_bound(const T& k) const {
    return binary_search([&](const T& x) { return !less(k, x); });
  }

  int count(const T& k) const {
    if (!multiset) return contains(k);
    return upper_bound(k) - lower_bound(k);
  }
  bool contains(const T& k) const {
    const node* t = root;
    while (t && !equal(t->key, k)) {
      t = less(k, t->key) ? t->left : t->right;
    }
    return t;
  }

  std::vector<T> enumerate() const {
    std::vector<T> elems(size());
    auto dfs = [&](auto self, const node* t, int i) {
      if (!t) return;
      elems[i + size(t->left)] = t->key;
      self(self, t->left, i);
      self(self, t->right, i + size(t->left) + 1);
    };
    dfs(dfs, root, 0);
    return elems;
  }

  int size() const { return size(root); }
  bool empty() const { return size() == 0; }

  friend std::ostream& operator<<(std::ostream& os, const treap& tp) {
    using io_utility::operator<<;
    return os << tp.enumerate();
  }

 private:
  struct node {
    T key;
    unsigned long long priority;
    int sub = 1;
    node* left = nullptr;
    node* right = nullptr;
    node() {}
    explicit node(const T& x) : key(x), priority(mt64()) {}
    node(const node& other)
        : key(other.key),
          priority(other.priority),
          sub(other.sub),
          left(other.left ? new node(*other.left) : nullptr),
          right(other.right ? new node(*other.right) : nullptr) {}
    node& operator=(const node& other) = delete;
    ~node() {
      delete left;
      delete right;
    }
  }* root = nullptr;

  static int size(const node* t) { return t ? t->sub : 0; }

  static void update(node* t) { t->sub = size(t->left) + size(t->right) + 1; }

  static bool less(const T& x, const T& y) { return Comp()(x, y); }
  static bool equal(const T& x, const T& y) {
    return !Comp()(x, y) && !Comp()(y, x);
  }

  std::pair<node*, node*> split(node* t, const T& k) {
    if (!t) return {nullptr, nullptr};
    if (less(k, t->key)) {
      auto s = split(t->left, k);
      t->left = s.second;
      update(t);
      return {s.first, t};
    } else {
      auto s = split(t->right, k);
      t->right = s.first;
      update(t);
      return {t, s.second};
    }
  }

  node* merge(node* left, node* right) {
    if (!left || !right) return left ? left : right;
    if (left->priority > right->priority) {
      left->right = merge(left->right, right);
      update(left);
      return left;
    } else {
      right->left = merge(left, right->left);
      update(right);
      return right;
    }
  }

  void insert(node*& t, node* p) {
    if (!t) {
      t = p;
    } else if (p->priority > t->priority) {
      std::tie(p->left, p->right) = split(t, p->key);
      update(p);
      t = p;
    } else {
      insert(p->key < t->key ? t->left : t->right, p);
      update(t);
    }
  }

  bool erase(node*& t, const T& k) {
    if (!t) {
      return false;
    } else if (equal(t->key, k)) {
      node* t2 = merge(t->left, t->right);
      t->left = t->right = nullptr;
      delete t;
      t = t2;
      return true;
    } else {
      bool res = erase(k < t->key ? t->left : t->right, k);
      update(t);
      return res;
    }
  }

  template <class F> int binary_search(F f) const {
    const node* t = root;
    int res = 0;
    while (t) {
      if (f(t->key)) {
        res += size(t->left) + 1;
        t = t->right;
      } else {
        t = t->left;
      }
    }
    return res;
  }
};

}  // namespace cp