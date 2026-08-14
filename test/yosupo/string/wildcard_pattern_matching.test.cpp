#define PROBLEM "https://judge.yosupo.jp/problem/wildcard_pattern_matching"

#include "poly/convolution_ll.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < int(b); i++)
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
    rep(i, 0, n) {
      if (_s[i] == '*') s[i] = 0;
      else s[i] = _s[i] - 'a' + 1;
    }
    rep(i, 0, m) {
      if (_t[i] == '*') t[i] = 0;
      else t[i] = _t[i] - 'a' + 1;
    }
  }

  vector<ll> s2(n), s3(n), t2(m), t3(m);
  rep(i, 0, n) s2[i] = s[i] * s[i];
  rep(i, 0, n) s3[i] = s[i] * s[i] * s[i];
  rep(i, 0, m) t2[i] = t[i] * t[i];
  rep(i, 0, m) t3[i] = t[i] * t[i] * t[i];

  reverse(t.begin(), t.end());
  reverse(t2.begin(), t2.end());
  reverse(t3.begin(), t3.end());

  auto c1 = convolution_ll(s3, t);
  auto c2 = convolution_ll(s2, t2);
  auto c3 = convolution_ll(s, t3);

  vector<ll> ans(n - m + 1);
  rep(i, 0, n - m + 1) {
    ans[i] = c1[m - 1 + i] - 2 * c2[m - 1 + i] + c3[m - 1 + i];
  }
  rep(i, 0, n - m + 1) cout << (ans[i] == 0);
}