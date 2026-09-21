#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "number/enumerate_primes.hpp"
#include "number/factorize.hpp"
#include "number/is_prime.hpp"
#include "number/linear_sieve.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

void test(int n) {
  linear_sieve sieve(n);
  assert(sieve.primes() == enumerate_primes(n));
  for (int i = 1; i <= n; i++) {
    auto f1 = sieve.factorize(i);
    auto f2 = factorize(i);
    assert(f1.size() == f2.size());
    for (int j = 0; j < int(f1.size()); j++) {
      assert(f1[j].first == f2[j].first);
      assert(f1[j].second == f2[j].second);
    }
  }
}

int main() {
  for (int i = 0; i <= 1000; i++) test(i);
  for (int i = 0; i < 10; i++) test(uniform(10001, 100000));
  cout << "Hello World\n";
}