#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "ds/dynamic_bitset.hpp"
#include "random/engine.hpp"
#include <cassert>
#include <bitset>
#include <iostream>
#include <utility>

using namespace std;
using namespace cp;

template <int k> void test(int q) {
  dynamic_bitset bs1(k);
  std::bitset<k> bs2;
  for (int i = 0; i < k; i++) bs1[i] = bs2[i] = uniform_bool();
  while (q--) {
    int t = uniform(0, 3);
    int x = uniform(0, k - 1);
    if (t == 0) {
      bs1[x] = !bs1[x];
      bs2[x] = !bs2[x];
    } else if (t == 1) {
      bs1.flip();
      bs2.flip();
    } else if (t == 2) {
      bs1 ^= (bs1 >> x) | bs1;
      bs2 ^= (bs2 >> x) | bs2;
    } else if (t == 3) {
      bs1 ^= (bs1 << x) & bs1;
      bs2 ^= (bs2 << x) & bs2;
    }
    for (int i = 0; i < k; i++) assert(bs1[i] == bs2[i]);
    assert(bs1.count() == int(bs2.count()));
  }
}

template <int i> void run_test() {
  constexpr int case_num = 7;
  constexpr std::pair<int, int> cases[] = {
      {1, 500000},   {10, 500000},  {255, 500000}, {256, 500000},
      {257, 500000}, {1000, 10000}, {1000000, 10}};

  test<cases[i].first>(cases[i].second);
  if constexpr (i < case_num - 1) {
    run_test<i + 1>();
  }
}

int main() {
  run_test<0>();
  cout << "Hello World\n";
}