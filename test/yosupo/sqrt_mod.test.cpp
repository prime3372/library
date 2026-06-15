#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include "../../number/sqrt_mod.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    ll y, p;
    cin >> y >> p;
    cout << sqrt_mod(y, p) << "\n";
  }
}
