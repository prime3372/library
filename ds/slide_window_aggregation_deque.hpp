#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

namespace cp {

template <class M> class slide_window_aggregation_deque {
  using S = typename M::S;

 public:
  slide_window_aggregation_deque() : prod0(M::e()), prod1(M::e()) {}

  void push_front(const S& x) { push0(x); }
  void push_back(const S& x) { push1(x); }

  void pop_front() {
    assert(!empty());
    if (val0.empty()) rebalance();
    val0.pop_back();
    cum0.pop_back();
    prod0 = cum0.empty() ? M::e() : cum0.back();
  }
  void pop_back() {
    assert(!empty());
    if (val1.empty()) rebalance();
    val1.pop_back();
    cum1.pop_back();
    prod1 = cum1.empty() ? M::e() : cum1.back();
  }

  S front() const {
    assert(!empty());
    return val0.empty() ? val1.front() : val0.back();
  }
  S back() const {
    assert(!empty());
    return val1.empty() ? val0.front() : val1.back();
  }
  S prod() const { return M::op(prod0, prod1); }

  int size() { return int(val0.size() + val1.size()); }
  bool empty() { return size() == 0; }

 private:
  std::vector<S> val0, val1, cum0, cum1;
  S prod0, prod1;

  void push0(S x) {
    val0.push_back(x);
    cum0.push_back(prod0 = M::op(x, prod0));
  }

  void push1(S x) {
    val1.push_back(x);
    cum1.push_back(prod1 = M::op(prod1, x));
  }

  void rebalance() {
    int n = int(val0.size() + val1.size());
    int s0 = n / 2 + (val0.empty() ? n % 2 : 0);
    std::vector<S> tmp = val0;
    std::reverse(tmp.begin(), val0.end());
    std::copy(val1.begin(), val1.end(), std::back_inserter(tmp));
    val0.clear();
    val1.clear();
    cum0.clear();
    cum1.clear();
    prod0 = M::e();
    prod1 = M::e();
    for (int i = s0 - 1; i >= 0; i--) push0(tmp[i]);
    for (int i = s0; i < n; i++) push1(tmp[i]);
  }
};

}  // namespace cp