#define PROBLEM "https://judge.yosupo.jp/problem/wildcard_pattern_matching"

#include "poly/convolution_ll.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s, t;
  cin >> s >> t;
  int n = int(s.size()), m = int(t.size());
  vector<ll> a1(n), a2(n), a3(n), b1(m), b2(m), b3(m);
  for (int i = 0; i < n; i++) {
    a1[i] = s[i] == '*' ? 0 : s[i] - 'a' + 1;
  }
  for (int i = 0; i < m; i++) {
    b1[i] = t[i] == '*' ? 0 : t[i] - 'a' + 1;
  }
  for (int i = 0; i < n; i++) a2[i] = a1[i] * a1[i];
  for (int i = 0; i < n; i++) a3[i] = a2[i] * a1[i];
  for (int i = 0; i < m; i++) b2[i] = b1[i] * b1[i];
  for (int i = 0; i < m; i++) b3[i] = b2[i] * b1[i];
  reverse(b1.begin(), b1.end());
  reverse(b2.begin(), b2.end());
  reverse(b3.begin(), b3.end());
  auto c1 = convolution_ll(a3, b1);
  auto c2 = convolution_ll(a2, b2);
  auto c3 = convolution_ll(a1, b3);
  vector<ll> ans(n - m + 1);
  for (int i = 0; i < n - m + 1; i++) {
    ans[i] = c1[m - 1 + i] - 2 * c2[m - 1 + i] + c3[m - 1 + i];
  }
  for (ll x : ans) cout << (x == 0);
  cout << "\n";
}