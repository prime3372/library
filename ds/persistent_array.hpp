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

  persistent_array() : n(0), log(0), init_val() {}
  explicit persistent_array(ull _n, T val = T())
      : n(_n), log(0), init_val(val) {
    for (ull i = n; i; i >>= shift) log++;
  }

  const T& operator[](ull i) const {
    assert(i < n);
    node* t = root;
    for (int k = 0; t && k < log; k++) {
      t = t->to[i & mask];
      i >>= shift;
    }
    return t ? t->val : init_val;
  }

  void set(ull i, const T& val) {
    assert(i < n);
    node* t = root;
    std::vector<node*> ps(log);
    for (int k = 0; t && k < log; k++) {
      ps[k] = t;
      t = t->to[(i >> (k * shift)) & mask];
    }
    node* cur = new node(val);
    for (int k = log - 1; k >= 0; k--) {
      node* nxt = ps[k] ? new node(*ps[k]) : new node();
      nxt->to[(i >> (k * shift)) & mask] = cur;
      cur = nxt;
    }
    root = cur;
  }

  void destructive_set(ull i, const T& val) {
    assert(i < n);
    node* t = root;
    for (int k = 0; k < log; k++) {
      if (!t) t = new node();
      t = t->to[i & mask];
      i >>= shift;
    }
    if (t) {
      t->val = val;
    } else {
      t = new node(val);
    }
  }

  node* snapshot() { return root; }
  void restore(node* new_root) { root = new_root; }

 private:
  static constexpr int shift = 4;
  static constexpr ull mask = (1 << shift) - 1;
  union node {
   private:
    friend persistent_array;
    std::array<node*, 1 << shift> to;
    T val;
    node() { to.fill(nullptr); }
    explicit node(const T& v) : val(v) {}
  }* root = nullptr;
  ull n;
  int log;
  T init_val;
};

}  // namespace cp