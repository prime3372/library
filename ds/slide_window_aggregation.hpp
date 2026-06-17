#pragma once

#include <cassert>
#include <vector>
#include "../algebra/monoid.hpp"

template <monoid M> struct slide_window_aggregation {
  using S = typename M::S;

public:
  slide_window_aggregation() : prod0(M::e()), prod1(M::e()) {}

  void push(S x) { push1(x); }
  void pop() {
    if (a0.empty()) transfer();
    assert(!a0.empty());
    a0.pop_back();
    cum0.pop_back();
    prod0 = cum0.empty() ? M::e() : cum0.back();
  }

  S prod() const { return M::op(prod0, prod1); }

  int size() const { return int(a0.size() + a1.size()); }
  bool empty() const { return size() == 0; }

private:
  std::vector<S> a0, a1, cum0, cum1;
  S prod0, prod1;

  void push0(S x) {
    a0.push_back(x);
    cum0.push_back(prod0 = M::op(x, prod0));
  }

  void push1(S x) {
    a1.push_back(x);
    cum1.push_back(prod1 = M::op(prod1, x));
  }

  void transfer() {
    while (!a1.empty()) {
      push0(a1.back());
      a1.pop_back();
      cum1.pop_back();
    }
    prod1 = M::e();
  }
};
