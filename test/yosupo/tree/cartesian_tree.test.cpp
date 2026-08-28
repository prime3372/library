#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"

#include "ds/cartesian_tree.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int& ai : a) cin >> ai;
  cartesian_tree cart(a);
  for (int p : cart.parent) {
    cout << (p == -1 ? cart.root : p) << " ";
  }
}