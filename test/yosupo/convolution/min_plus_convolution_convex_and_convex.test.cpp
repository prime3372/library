#define PROBLEM \
  "https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex"

#include "convex/min_plus_convolution_both_convex.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<int> a(n), b(m);
  for (int& ai : a) cin >> ai;
  for (int& bi : b) cin >> bi;
  auto c = min_plus_convolution_both_convex(a, b);
  for (int& ci : c) cout << ci << " ";
}