#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "../../ds/hash_map.hpp"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  hash_map<ll> mp;
  while (q--) {
    int t;
    cin >> t;
    if (!t) {
      ll k, v;
      cin >> k >> v;
      mp[k] = v;
    } else {
      ll k;
      cin >> k;
      cout << mp[k] << "\n";
    }
  }
}
