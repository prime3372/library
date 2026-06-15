#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "../../number/binom_mod.hpp"
#include "../../util/dynamic_modint.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, m;
  cin >> t >> m;
  modint::set_mod(m);
  binom_mod<modint> binom(int(1e7));
  while (t--) {
    int n, k;
    cin >> n >> k;
    cout << binom(n, k) << "\n";
  }
}
