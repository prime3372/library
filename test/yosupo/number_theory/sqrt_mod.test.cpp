#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include "number/sqrt_mod.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    ll y, p;
    cin >> y >> p;
    cout << sqrt_mod(y, p) << "\n";
  }
}