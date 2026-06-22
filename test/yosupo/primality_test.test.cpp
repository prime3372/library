#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include "../../number/is_prime.hpp"
#include <bits/stdc++.h>

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
