#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <utility>

#include "ds/treap_base.hpp"
#include "random/base.hpp"

namespace cp {

namespace internal {

template <class M> struct segtreap_node {
  using S = typename M::S;
  S val, prod;
  int sub = 1;
  bool rev = false;
  segtreap_node* left = nullptr;
  segtreap_node* right = nullptr;
  unsigned long long priority;

  segtreap_node() {}
  explicit segtreap_node(const S& x) : val(x), prod(x), priority(mt64()) {}
  ~segtreap_node() {
    delete left;
    delete right;
  }
};

}  // namespace internal

template <class M, auto rev = std::identity()>
class segtreap : public treap_base<internal::segtreap_node<M>> {
  using S = typename M::S;
  using node = internal::segtreap_node<M>;
  using base = treap_base<node>;

 public:
  segtreap() {}
  explicit segtreap(int n) { build(std::vector<S>(n)); }
  explicit segtreap(int n, S val) { build(std::vector<S>(n, val)); }
  explicit segtreap(const std::vector<S>& v) { build(v); }

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return M::e();
    auto s = split(root, l);
    auto t = split(s.second, r - l);
    auto res = t.first->prod;
    root = merge(s.first, merge(t.first, t.second));
    return res;
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
  }
};

}  // namespace cp