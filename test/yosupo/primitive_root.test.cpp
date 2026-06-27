#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"

#include "../../number/primitive_root.hpp"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  while (q--) {
    ll p;
    cin >> p;
    cout << primitive_root(p) << "\n";
  }
}
