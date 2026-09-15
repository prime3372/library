#pragma once

#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>

#include "ds/implicit_treap_base.hpp"
#include "random/engine.hpp"
#include "util/memory_pool.hpp"

namespace cp {

template <class S, class F, auto id> struct implicit_treap_acted_monoid_node {
  using self = implicit_treap_acted_monoid_node;
  inline static memory_pool<implicit_treap_acted_monoid_node> pool;

  S val, prod;
  F lz = id();
  int sub = 1;
  bool rev = false;
  bool lzflag = false;
  unsigned long long priority;
  self* left = nullptr;
  self* right = nullptr;

  implicit_treap_acted_monoid_node() {}
  explicit implicit_treap_acted_monoid_node(const S& x)
      : val(x), prod(x), priority(rng()) {}
  implicit_treap_acted_monoid_node(const self& other)
      : val(other.val),
        prod(other.prod),
        lz(other.lz),
        sub(other.sub),
        rev(other.rev),
        lzflag(other.lzflag),
        priority(other.priority),
        left(other.left ? new self(*other.left) : nullptr),
        right(other.right ? new self(*other.right) : nullptr) {}
  self& operator=(const self&) = delete;
  ~implicit_treap_acted_monoid_node() {
    delete left;
    delete right;
  }
  void* operator new(std::size_t) { return pool.malloc(); }
  void operator delete(void* ptr) { return pool.free((self*)(ptr)); }
};

template <class S, auto op, auto e, class F, auto act, auto compose, auto id,
          auto reverse = std::identity()>
class implicit_treap_acted_monoid
    : public implicit_treap_base<
          implicit_treap_acted_monoid_node<S, F, id>,
          implicit_treap_acted_monoid<S, op, e, F, act, compose, id, reverse>> {
 public:
  implicit_treap_acted_monoid() {}
  explicit implicit_treap_acted_monoid(int n, const S& val = e())
      : implicit_treap_acted_monoid(std::vector<S>(n, val)) {}
  explicit implicit_treap_acted_monoid(const std::vector<S>& v) : base(v) {}

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return e();
    auto s1 = split(root, l);
    auto s2 = split(s1.second, r - l);
    S res = s2.first->prod;
    root = merge(s1.first, merge(s2.first, s2.second));
    return res;
  }

  void apply(int l, int r, const F& f) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return;
    auto s1 = split(root, l);
    auto s2 = split(s1.second, r - l);
    all_apply(s2.first, f);
    root = merge(s1.first, merge(s2.first, s2.second));
  }

 private:
  using node = implicit_treap_acted_monoid_node<S, F, id>;
  using base = implicit_treap_base<node, implicit_treap_acted_monoid>;
  friend base;
  using base::merge;
  using base::root;
  using base::size;
  using base::split;

  static void toggle(node* t) {
    std::swap(t->left, t->right);
    t->prod = reverse(t->prod);
    t->rev = !t->rev;
  }

  static void update(node* t) {
    t->sub = size(t->left) + size(t->right) + 1;
    t->prod = t->val;
    if (t->left) t->prod = op(t->left->prod, t->prod);
    if (t->right) t->prod = op(t->prod, t->right->prod);
  }

  static void push(node* t) {
    if (t->rev) {
      if (t->left) toggle(t->left);
      if (t->right) toggle(t->right);
      t->rev = false;
    }
    if (t->lzflag) {
      if (t->left) all_apply(t->left, t->lz);
      if (t->right) all_apply(t->right, t->lz);
      t->lz = id();
      t->lzflag = false;
    }
  }

  static void all_apply(node* t, const F& f) {
    t->lz = compose(f, t->lz);
    t->val = act(f, t->val);
    t->prod = act(f, t->prod);
    t->lzflag = true;
  }
};

}  // namespace cp