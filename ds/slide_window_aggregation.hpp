#pragma once

#include <cassert>
#include <iostream>
#include <vector>

namespace cp {

template <class M> class slide_window_aggregation {
  using S = typename M::S;

 public:
  slide_window_aggregation() : prod0(M::e()), prod1(M::e()) {}

  void push(const S& x) { push1(x); }
  void pop() {
    assert(!empty());
    if (val0.empty()) transfer();
    val0.pop_back();
    cum0.pop_back();
    prod0 = cum0.empty() ? M::e() : cum0.back();
  }

  S front() const {
    assert(!empty());
    return val0.empty() ? val1.front() : val0.back();
  }
  S prod() const { return M::op(prod0, prod1); }

  int size() const { return int(val0.size() + val1.size()); }
  bool empty() const { return size() == 0; }

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

  void transfer() {
    while (!val1.empty()) {
      push0(val1.back());
      val1.pop_back();
      cum1.pop_back();
    }
    prod1 = M::e();
  }
};

}  // namespace cp