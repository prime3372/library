#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "random/engine.hpp"
#include "util/io_float128.hpp"
#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace cp;
using namespace io;
using ll = long long;
using f128 = __float128;

f128 abs_f128(f128 x) { return x < 0 ? -x : x; }

void test(f128 p10, int prec) {
  stringstream ss;
  ss << fixed << setprecision(prec);
  f128 x = uniform01();
  x *= uniform01();
  x *= uniform01();
  x *= p10;
  if (uniform_bool()) x = -x;
  ss << x;
  f128 y;
  ss >> y;
  assert(abs_f128((x - y) / x) < 1e-32);
}

void solve() {
  int a, b;
  cin >> a >> b;
  cout << a + b << "\n";
}

int main() {
  pair<f128, int> cases[] = {{1e-60, 120}, {1e-45, 105}, {1e-30, 90},
                             {1e-15, 75},  {1, 60},      {1e15, 45},
                             {1e30, 30},   {1e45, 15},   {1e60, 0}};
  for (auto [p10, prec] : cases) {
    for (int i = 0; i < 10000; i++) test(p10, prec);
  }
  solve();
}