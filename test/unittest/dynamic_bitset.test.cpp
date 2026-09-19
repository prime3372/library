#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "random/engine.hpp"
#include "ds/dynamic_bitset.hpp"
#include <cassert>
#include <bitset>
#include <iostream>

using namespace std;
using namespace cp;

template <int k> void test(int n) {
  dynamic_bitset bs1(k);
  std::bitset<k> bs2;
  for (int i = 0; i < k; i++) bs1[i] = bs2[i] = uniform_bool();
  for (int i = 0; i < n; i++) {
    int t = uniform(0, 3);
    int x = uniform(0, k - 1);
    if (t == 0) {
      bs1[x] = !bs1[x];
      bs2[x] = !bs2[x];
    } else if (t == 1) {
      bs1.flip();
      bs2.flip();
    } else if (t == 2) {
      bs1 ^= bs1 >> x;
      bs2 ^= bs2 >> x;
    } else if (t == 3) {
      bs1 ^= bs1 << x;
      bs2 ^= bs2 << x;
    }
    for (int j = 0; j < k; j++) assert(bs1[j] == bs2[j]);
    assert(bs1.count() == int(bs2.count()));
  }
}

int main() {
  test<1>(500000);
  test<10>(500000);
  test<255>(500000);
  test<256>(500000);
  test<257>(500000);
  test<1000>(10000);
  test<1000000>(10);
  cout << "Hello World\n";
}