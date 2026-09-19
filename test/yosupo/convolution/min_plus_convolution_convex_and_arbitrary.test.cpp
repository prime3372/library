#define PROBLEM \
  "https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary"

#include "convex/max_plus_convolution.hpp"
#include "convex/min_plus_convolution.hpp"
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
  for (int& x : a) cin >> x;
  for (int& x : b) cin >> x;
  auto c1 = min_plus_convolution(a, b);
  for (int& x : a) x = -x;
  for (int& x : b) x = -x;
  auto c2 = max_plus_convolution(a, b);
  for (int i = 0; i < n + m - 1; i++) assert(c1[i] == -c2[i]);
  for (int& x : c1) cout << x << " ";
}