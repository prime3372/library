#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_integer"

#include "../../number/isqrt.hpp"
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    unsigned long long a;
    int k;
    cin >> a >> k;
    cout << kth_root(a, k) << "\n";
  }
}
