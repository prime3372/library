#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include "../../number/is_prime.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  while (q--) {
    ll n;
    cin >> n;
    cout << (is_prime(n) ? "Yes" : "No") << "\n";
  }
}
