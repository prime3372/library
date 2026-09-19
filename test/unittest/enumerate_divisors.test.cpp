#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "random/engine.hpp"
#include "number/enumerate_divisors.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void test(int n) {
  auto divs = enumerate_divisors(n);
  for (int i = 1; i < n; i++) {
    bool is_divisor = n % i == 0;
    auto lb = lower_bound(divs.begin(), divs.end(), i);
    auto ub = upper_bound(divs.begin(), divs.end(), i);
    assert(ub - lb <= 1);
    assert((is_divisor) == (lb != ub));
  }
}

int main() {
  for (int i = 1; i <= 1000; i++) test(i);
  for (int i = 0; i < 100; i++) test(uniform(1001, 100000));
  cout << "Hello World\n";
}