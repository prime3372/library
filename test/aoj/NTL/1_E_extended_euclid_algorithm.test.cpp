#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E"

#include "number/ext_gcd.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ll a, b;
  cin >> a >> b;
  auto [g, x1] = ext_gcd(a, b);
  ll y1 = (g - a * x1) / b;
  ll x2 = x1 - b / g, y2 = y1 + a / g;
  if (abs(x1) + abs(y1) < abs(x2) + abs(y2)) {
    cout << x1 << " " << y1 << "\n";
  } else {
    cout << x2 << " " << y2 << "\n";
  }
}