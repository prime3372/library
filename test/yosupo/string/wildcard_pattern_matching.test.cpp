#define PROBLEM "https://judge.yosupo.jp/problem/wildcard_pattern_matching"

#include "poly/convolution_ll.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  int n, m;
  vector<ll> s, t;
  {
    string _s, _t;
    cin >> _s >> _t;
    n = int(_s.size());
    m = int(_t.size());
    s.resize(n); t.resize(m);
    for (int i = 0; i < n; i++) {
      if (_s[i] == '*') s[i] = 0;
      else s[i] = _s[i] - 'a' + 1;
    }
    for (int i = 0; i < m; i++) {
      if (_t[i] == '*') t[i] = 0;
      else t[i] = _t[i] - 'a' + 1;
    }
  }

  vector<ll> s2(n), s3(n), t2(m), t3(m);
  for (int i = 0; i < n; i++) s2[i] = s[i] * s[i];
  for (int i = 0; i < n; i++) s3[i] = s[i] * s[i] * s[i];
  for (int i = 0; i < m; i++) t2[i] = t[i] * t[i];
  for (int i = 0; i < m; i++) t3[i] = t[i] * t[i] * t[i];

  reverse(t.begin(), t.end());
  reverse(t2.begin(), t2.end());
  reverse(t3.begin(), t3.end());

  auto c1 = convolution_ll(s3, t);
  auto c2 = convolution_ll(s2, t2);
  auto c3 = convolution_ll(s, t3);

  vector<ll> ans(n - m + 1);
  for (int i = 0; i < n - m + 1; i++) {
    ans[i] = c1[m - 1 + i] - 2 * c2[m - 1 + i] + c3[m - 1 + i];
  }
  for (ll& x : ans) cout << (x == 0);
  cout << "\n";
}