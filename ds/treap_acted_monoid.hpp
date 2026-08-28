#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "ds/treap_base.hpp"
#include "random/base.hpp"

namespace cp {

namespace internal {

template <class M> struct treap_acted_monoid_node {
  using S = typename M::S;
  using F = typename M::F;
  S val, prod;
  F lz = M::id();
  int sub = 1;
  bool rev = false;
  unsigned long long priority;
  treap_acted_monoid_node* left = nullptr;
  treap_acted_monoid_node* right = nullptr;

  treap_acted_monoid_node() {}
  explicit treap_acted_monoid_node(const S& x)
      : val(x), prod(x), priority(mt64()) {}
  treap_acted_monoid_node(const treap_acted_monoid_node& other)
      : val(other.val),
        prod(other.prod),
        lz(other.lz),
        sub(other.sub),
        rev(other.rev),
        priority(other.priority),
        left(other.left ? new treap_acted_monoid_node(*other.left) : nullptr),
        right(other.right ? new treap_acted_monoid_node(*other.right)
                          : nullptr) {}
  treap_acted_monoid_node& operator=(const treap_acted_monoid_node&) = delete;
  ~treap_acted_monoid_node() {
    delete left;
    delete right;
  }
};

}  // namespace internal

template <class M, auto rev = std::identity()>
class treap_acted_monoid
    : public treap_base<internal::treap_acted_monoid_node<M>,
                        treap_acted_monoid<M, rev>> {
  using S = typename M::S;
  using F = typename M::F;
  using node = internal::treap_acted_monoid_node<M>;
  using base = treap_base<node, treap_acted_monoid>;

 public:
  using base::base;

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return M::e();
    auto s = split(root, l);
    auto t = split(s.second, r - l);
    auto res = t.first->prod;
    root = merge(s.first, merge(t.first, t.second));
    return res;
  }

  void apply(int l, int r, const F& f) {
    assert(0 <= l && l <= r && r <= size());
    if (l == r) return;
    auto s = split(root, l);
    auto t = split(s.second, r - l);
    all_apply(t.first, f);
    root = merge(s.first, merge(t.first, t.second));
  }

 private:
  using base::merge;
  using base::root;
  using base::size;
  using base::split;
  friend base;

  static void toggle(node* p) {
    std::swap(p->left, p->right);
    p->prod = rev(p->prod);
    p->rev = !p->rev;
  }

  static void update(node* p) {
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

  static void push(node* p) {
    if (p->rev) {
      if (p->left) toggle(p->left);
      if (p->right) toggle(p->right);
      p->rev = false;
    }
    if (p->left) all_apply(p->left, p->lz);
    if (p->right) all_apply(p->right, p->lz);
    p->lz = M::id();
  }

  static void all_apply(node* p, F f) {
    p->lz = M::composition(f, p->lz);
    p->val = M::mapping(f, p->val);
    p->prod = M::mapping(f, p->prod);
  }
};

}  // namespace cp