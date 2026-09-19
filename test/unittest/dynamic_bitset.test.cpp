#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "random/engine.hpp"
#include "ds/dynamic_bitset.hpp"
#include <cassert>
#include <bitset>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

template <int k> void random(int n) {
  dynamic_bitset bs1(k);
  std::bitset<k> bs2;
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
      bs1 ^= (bs1 >> x) | (bs1 << (k - x));
      bs2 ^= (bs2 >> x) | (bs2 << (k - x));
    } else {
      bs1 &= (bs1 >> x) | (bs1 << (k - x));
      bs2 &= (bs2 >> x) | (bs2 << (k - x));
    }
    for (int j = 0; j < k; j++) assert(bs1[j] == bool(bs2[j]));
    assert(bs1.count() == int(bs2.count()));
  }
}
void width_1() { random<1>(100000); }
void width_100() { random<100>(100000); }
void width_10000() { random<10000>(1000); }
void width_1000000() { random<1000000>(10); }

int main() {
  for (int i = 0; i < 10; i++) width_1();
  for (int i = 0; i < 10; i++) width_100();
  for (int i = 0; i < 10; i++) width_10000();
  for (int i = 0; i < 10; i++) width_1000000();
  cout << "Hello World\n";
}