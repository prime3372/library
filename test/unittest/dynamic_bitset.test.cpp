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
void width_1() { random<1>(500000); }
void width_10() { random<10>(500000); }
void width_255() { random<255>(500000); }
void width_256() { random<256>(500000); }
void width_257() { random<257>(500000); }
void width_1000() { random<1000>(10000); }
void width_1000000() { random<1000000>(10); }

int main() {
  width_1();
  width_10();
  width_255();
  width_256();
  width_257();
  width_1000();
  width_1000000();
  cout << "Hello World\n";
}