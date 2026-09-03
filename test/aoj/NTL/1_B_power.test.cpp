#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_B"

#include "number/pow_mod.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  int m, n;
  cin >> m >> n;
  cout << pow_mod(m, n, int(1e9 + 7)) << "\n";
}