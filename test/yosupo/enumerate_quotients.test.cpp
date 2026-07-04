#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_quotients"

#include "../../number/enumerate_quotients.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  cin >> n;
  auto qs = enumerate_quotients(n);
  cout << qs.size() << "\n";
  for (ll q : qs) cout << q << " ";
}
