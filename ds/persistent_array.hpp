#pragma once

#include <array>
#include <cassert>
#include <utility>
#include <vector>

namespace cp {

template <class T> class persistent_array {
  using ull = unsigned long long;
  union node;

 public:
  using node_ptr = node*;

  persistent_array() : n(0), depth(0), init_val() {}
  explicit persistent_array(ull _n, T val = T())
      : root(new node()), n(_n), depth(0), init_val(val) {
    for (ull i = n; i; i >>= shift) depth++;
  }

  const T& operator[](ull k) const {
    assert(k < n);
    node* t = root;
    for (int i = 0; t && i < depth; i++) {
      t = t->to[k & mask];
      k >>= shift;
    }
    return t ? t->val : init_val;
  }

  void set(ull k, const T& val) {
    assert(k < n);
    node* t = root;
    std::vector<std::pair<node*, int>> path(depth);
    for (int i = 0; i < depth; i++) {
      path[i] = {t, k & mask};
      t = t ? t->to[k & mask] : nullptr;
      k >>= shift;
    }
    node* cur = new node(val);
    for (int i = depth - 1; i >= 0; i--) {
      auto [par, j] = path[i];
      node* nxt = par ? new node(*par) : new node();
      nxt->to[j] = cur;
      cur = nxt;
    }
    root = cur;
  }

  void destructive_set(ull k, const T& val) {
    assert(k < n);
    node* t = root;
    for (int i = 0; t && i < depth; i++) {
      t = t->to[k & mask];
      k >>= shift;
    }
    t->val = val;
  }

  node* snapshot() { return root; }
  void restore(node* new_root) { root = new_root; }

 private:
  static constexpr int shift = 4;
  static constexpr int mask = (1 << shift) - 1;
  union node {
   private:
    friend persistent_array;
    std::array<node*, 1 << shift> to;
    T val;
    node() { to.fill(nullptr); }
    explicit node(const T& v) : val(v) {}
  }* root = nullptr;
  ull n;
  int depth;
  T init_val;
};

}  // namespace cp