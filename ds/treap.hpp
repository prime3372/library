#pragma once

#include <algorithm>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "ds/cartesian-tree.hpp"
#include "random/engine.hpp"

namespace cp {

template <class T, bool multiset, class Compare = std::less<T>> struct Treap {
 public:
  Treap() {}
  explicit Treap(std::vector<T> v) {
    if (v.empty()) return;
    int n = int(v.size());
    for (int i = 0; i < n - 1; i++) {
      if (less(v[i + 1], v[i])) {
        std::sort(v.begin(), v.end(), less);
        break;
      }
    }
    if (!multiset) {
      v.erase(std::unique(v.begin(), v.end(), equiv), v.end());
      n = int(v.size());
    }
    std::vector<Node*> ps(n);
    std::vector<unsigned long long> pr(n);
    for (int i = 0; i < n; i++) {
      ps[i] = new Node(v[i]);
      pr[i] = ps[i]->priority;
    }
    CartesianTree cart(pr, std::greater<unsigned long long>());
    for (int i = 0; i < n; i++) {
      if (cart.left[i] != -1) ps[i]->left = ps[cart.left[i]];
      if (cart.right[i] != -1) ps[i]->right = ps[cart.right[i]];
    }
    auto dfs = [&](auto self, Node* t) -> void {
      if (!t) return;
      self(self, t->left);
      self(self, t->right);
      update(t);
    };
    dfs(dfs, root = ps[cart.root]);
  }
  Treap(const Treap& other) {
    auto dfs = [&](auto self, const Node* t) -> Node* {
      if (!t) return nullptr;
      Node* ptr = new Node(*t);
      ptr->left = self(self, t->left);
      ptr->right = self(self, t->right);
      return ptr;
    };
    root = dfs(dfs, other.root);
  }
  Treap(Treap&& other) noexcept : root(other.root) { other.root = nullptr; }
  Treap& operator=(Treap other) {
    std::swap(root, other.root);
    return *this;
  }
  ~Treap() {
    auto dfs = [&](auto self, Node* t) -> void {
      if (!t) return;
      self(self, t->left);
      self(self, t->right);
      delete t;
    };
    dfs(dfs, root);
  }

  std::conditional_t<multiset, void, bool> insert(const T& k) {
    if constexpr (multiset) {
      insert(root, new Node(k));
    } else {
      return contains(k) ? false : (insert(root, new Node(k)), true);
    }
  }
  template <class... Args>
  std::conditional_t<multiset, void, bool> emplace(Args&&... args) {
    return insert(T(std::forward<Args>(args)...));
  }

  bool erase(const T& k) { return erase(root, k); }

  const T& operator[](int i) const {
    assert(0 <= i && i < size());
    const Node* t = root;
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
  const T& min() const {
    assert(!empty());
    return (*this)[0];
  }
  const T& max() const {
    assert(!empty());
    return (*this)[size() - 1];
  }

  int lower_bound(const T& k) const {
    const Node* t = root;
    int res = 0;
    while (t) {
      if (!less(t->key, k)) {
        t = t->left;
      } else {
        res += size(t->left) + 1;
        t = t->right;
      }
    }
    return res;
  }
  int upper_bound(const T& k) const {
    const Node* t = root;
    int res = 0;
    while (t) {
      if (less(k, t->key)) {
        t = t->left;
      } else {
        res += size(t->left) + 1;
        t = t->right;
      }
    }
    return res;
  }

  int count(const T& k) const {
    if (!multiset) return contains(k);
    return upper_bound(k) - lower_bound(k);
  }
  bool contains(const T& k) const {
    const Node* t = root;
    while (t && !equiv(t->key, k)) t = less(k, t->key) ? t->left : t->right;
    return t;
  }

  int size() const { return size(root); }
  bool empty() const { return size() == 0; }

 private:
  struct Node {
    T key;
    int sub = 1;
    unsigned long long priority;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(const T& x) : key(x), priority(rng()) {}
  }* root = nullptr;

  static bool less(const T& x, const T& y) { return Compare{}(x, y); }
  static bool equiv(const T& x, const T& y) {
    return !Compare{}(x, y) && !Compare{}(y, x);
  }

  int size(const Node* t) const { return t ? t->sub : 0; }

  void update(Node* t) { t->sub = size(t->left) + size(t->right) + 1; }

  std::pair<Node*, Node*> split(Node* t, const T& k) {
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

  Node* merge(Node* left, Node* right) {
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

  void insert(Node*& t, Node* p) {
    if (!t) {
      t = p;
    } else if (p->priority > t->priority) {
      std::tie(p->left, p->right) = split(t, p->key);
      update(p);
      t = p;
    } else {
      insert(less(p->key, t->key) ? t->left : t->right, p);
      update(t);
    }
  }

  bool erase(Node*& t, const T& k) {
    if (!t) return false;
    if (equiv(t->key, k)) {
      Node* t2 = merge(t->left, t->right);
      delete t;
      t = t2;
      return true;
    }
    bool res = erase(less(k, t->key) ? t->left : t->right, k);
    update(t);
    return res;
  }
};

}  // namespace cp