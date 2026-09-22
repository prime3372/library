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

  const T& operator[](ull i) const {
    assert(i < n);
    node* t = root;
    for (int d = 0; t && d < depth; d++) {
      t = t->to[i & mask];
      i >>= shift;
    }
    return t ? t->val : init_val;
  }

  void set(ull i, const T& val) {
    assert(i < n);
    node* t = root;
    std::vector<std::pair<node*, int>> path(depth);
    for (int d = 0; d < depth; d++) {
      path[d] = {t, i & mask};
      t = t ? t->to[i & mask] : nullptr;
      i >>= shift;
    }
    node* cur = new node(val);
    for (int d = depth - 1; d >= 0; d--) {
      auto [par, j] = path[d];
      node* nxt = par ? new node(*par) : new node();
      nxt->to[j] = cur;
      cur = nxt;
    }
    root = cur;
  }

  void destructive_set(ull i, const T& val) {
    assert(i < n);
    node* t = root;
    for (int d = 0; t && d < depth; d++) {
      t = t->to[i & mask];
      i >>= shift;
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