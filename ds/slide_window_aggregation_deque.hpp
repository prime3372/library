#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

#include "algebra/monoid.hpp"

namespace cp {

template <monoid M> struct slide_window_aggregation_deque {
private:
  using S = typename M::S;

public:
  slide_window_aggregation_deque() : prod0(M::e()), prod1(M::e()) {}

  void push_front(S x) { push0(x); }

  void push_back(S x) { push1(x); }

  void pop_front() {
    if (a0.empty()) rebalance();
    assert(!a0.empty());
    a0.pop_back(), cum0.pop_back();
    prod0 = cum0.empty() ? M::e() : cum0.back();
  }

  void pop_back() {
    if (a1.empty()) rebalance();
    assert(!a1.empty());
    a1.pop_back(), cum1.pop_back();
    prod1 = cum1.empty() ? M::e() : cum1.back();
  }

  S front() const { return a0.empty() ? a1.front() : a0.back(); }
  S back() const { return a1.empty() ? a0.front() : a1.back(); }
  S prod() { return M::op(prod0, prod1); }

  int size() { return int(a0.size() + a1.size()); }
  int empty() { return size() == 0; }

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

  void rebalance() {
    int n = a0.size() + a1.size();
    int s0 = n / 2 + (a0.empty() ? n % 2 : 0);
    std::vector<S> a = a0;
    std::reverse(a.begin(), a.end());
    std::copy(a1.begin(), a1.end(), std::back_inserter(a));
    a0.clear(); cum0.clear(); prod0 = M::e();
    a1.clear(); cum1.clear(); prod1 = M::e();
    for (int i = s0 - 1; i >= 0; i--) push0(a[i]);
    for (int i = s0; i < n; i++) push1(a[i]);
  }
};

} // namespace cp