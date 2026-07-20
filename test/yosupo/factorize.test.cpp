#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "number/factorize.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;
using ll = long long;

int main() {
  int t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    auto fac = factorize(n);
    int k = 0;
    for (auto f : fac) k += f.second;
    cout << k << " ";
    for (auto f : fac) {
      rep(i, 0, f.second) cout << f.first << " ";
    }
    cout << "\n";
  }
}