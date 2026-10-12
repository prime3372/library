#pragma once

#include <array>
#include <cassert>
#include <utility>
#include <vector>

namespace cp {

template <class T> struct PersistentArray {
  using ull = unsigned long long;
  union Node;

 public:
  using node_ptr = Node*;

  PersistentArray() : n(0), log(0), init_val() {}
  explicit PersistentArray(ull _n, T val = T()) : n(_n), log(0), init_val(val) {
    for (ull i = n; i; i >>= shift) log++;
  }

  const T& operator[](ull i) const {
    assert(i < n);
    Node* t = root;
    for (int k = 0; t && k < log; k++) {
      t = t->to[i & mask];
      i >>= shift;
    }
    return t ? t->val : init_val;
  }

  void set(ull i, const T& val) {
    assert(i < n);
    Node* t = root;
    std::vector<Node*> ps(log);
    for (int k = 0; t && k < log; k++) {
      ps[k] = t;
      t = t->to[(i >> (k * shift)) & mask];
    }
    Node* cur = new Node(val);
    for (int k = log - 1; k >= 0; k--) {
      Node* nxt = ps[k] ? new Node(*ps[k]) : new Node();
      nxt->to[(i >> (k * shift)) & mask] = cur;
      cur = nxt;
    }
    root = cur;
  }

  void destructive_set(ull i, const T& val) {
    assert(i < n);
    Node* t = root;
    for (int k = 0; k < log; k++) {
      if (!t) t = new Node();
      t = t->to[i & mask];
      i >>= shift;
    }
    if (t)
      t->val = val;
    else
      t = new Node(val);
  }

  Node* snapshot() { return root; }
  void restore(Node* new_root) { root = new_root; }

 private:
  static constexpr int shift = 4;
  static constexpr ull mask = (1 << shift) - 1;
  union Node {
   private:
    friend PersistentArray;
    std::array<Node*, 1 << shift> to;
    T val;
    Node() { to.fill(nullptr); }
    explicit Node(const T& v) : val(v) {}
  }* root = nullptr;
  ull n;
  int log;
  T init_val;
};

}  // namespace cp