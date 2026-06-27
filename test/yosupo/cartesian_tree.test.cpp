#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"

#include "../../tree/cartesian_tree.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  cin >> n;
  std::vector<int> a(n);
  rep(i, 0, n) cin >> a[i];
  cartesian_tree<false> cart(a);
  for (int p : cart.parent) cout << p << " ";
}
