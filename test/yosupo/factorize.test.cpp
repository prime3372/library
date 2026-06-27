#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../../number/factorize.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using ll = long long;

int main() {
  int t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    auto fs = factorize(n);
    int k = 0;
    for (auto f : fs) k += f.second;
    cout << k << " ";
    for (auto f : fs) {
      rep(i, 0, f.second) cout << f.first << " ";
    }
    cout << "\n";
  }
}
