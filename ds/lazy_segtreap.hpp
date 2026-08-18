#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "ds/treap_base.hpp"
#include "random/base.hpp"

namespace cp {

namespace internal {

template <class M> struct lazy_segtreap_node {
  using S = typename M::S;
  using F = typename M::F;
  S val, prod;
  F lz = M::id();
  int sub = 1;
  bool rev = false;
  lazy_segtreap_node* left = nullptr;
  lazy_segtreap_node* right = nullptr;
  unsigned long long priority;

  lazy_segtreap_node() {}
  explicit lazy_segtreap_node(const S& x) : val(x), prod(x), priority(mt64()) {}
  ~lazy_segtreap_node() {
    delete left;
    delete right;
  }
};

}  // namespace internal

template <class M, auto rev = std::identity()>
class lazy_segtreap : public treap_base<internal::lazy_segtreap_node<M>> {
 public:
  using S = typename M::S;
  using F = typename M::F;
  using node = internal::lazy_segtreap_node<M>;
  using base = treap_base<node>;

  lazy_segtreap() {}
  explicit lazy_segtreap(int n) { build(std::vector<S>(n)); }
  explicit lazy_segtreap(int n, S val) { build(std::vector<S>(n, val)); }
  explicit lazy_segtreap(const std::vector<S>& v) { build(v); }

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return M::e();
    auto s = split(root, l);
    auto t = split(s.second, r - l);
    auto res = t.first->prod;
    root = merge(s.first, merge(t.first, t.second));
    return res;
  }

  void apply(int l, int r, F f) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return;
    auto s = split(root, l);
    auto t = split(s.second, r - l);
    all_apply(t.first, f);
    root = merge(s.first, merge(t.first, t.second));
  }

 protected:
  using base::build;
  using base::merge;
  using base::root;
  using base::size;
  using base::split;

  void toggle(node* p) override {
    std::swap(p->left, p->right);
    p->prod = rev(p->prod);
    p->rev = !p->rev;
  }

  void update(node* p) override {
    p->sub = 1;
    p->prod = p->val;
    if (p->left) {
      p->sub += p->left->sub;
      p->prod = M::op(p->left->prod, p->prod);
    }
    if (p->right) {
      p->sub += p->right->sub;
      p->prod = M::op(p->prod, p->right->prod);
    }
  }

  void push(node* p) override {
    if (p->rev) {
      if (p->left) toggle(p->left);
      if (p->right) toggle(p->right);
      p->rev = false;
    }
    if (p->left) all_apply(p->left, p->lz);
    if (p->right) all_apply(p->right, p->lz);
    p->lz = M::id();
  }

  void all_apply(node* p, F f) {
    p->lz = M::composition(f, p->lz);
    p->val = M::composition(f, p->val);
    p->prod = M::mapping(f, p->prod);
  }
};

}  // namespace cp