#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <utility>

#include "ds/treap_base.hpp"
#include "random/base.hpp"

namespace cp {

namespace internal {

template <class M> struct treap_monoid_node {
  using S = typename M::S;
  S val, prod;
  int sub = 1;
  bool rev = false;
  treap_monoid_node* left = nullptr;
  treap_monoid_node* right = nullptr;
  unsigned long long priority;

  treap_monoid_node() {}
  explicit treap_monoid_node(S x) : val(x), prod(x), priority(mt64()) {}
  ~treap_monoid_node() {
    delete left;
    delete right;
  }
};

}  // namespace internal

template <class M, auto rev = std::identity()>
class treap_monoid : public treap_base<internal::treap_monoid_node<M>> {
  using S = typename M::S;
  using node = internal::treap_monoid_node<M>;
  using base = treap_base<node>;

 public:
  treap_monoid() {}
  explicit treap_monoid(int n) { build(std::vector<S>(n)); }
  explicit treap_monoid(int n, S val) { build(std::vector<S>(n, val)); }
  explicit treap_monoid(const std::vector<S>& v) { build(v); }

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