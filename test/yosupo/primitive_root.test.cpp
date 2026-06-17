#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"

#include "../../number/primitive_root.hpp"
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
    ll p;
    cin >> p;
    cout << primitive_root(p) << "\n";
  }
}
