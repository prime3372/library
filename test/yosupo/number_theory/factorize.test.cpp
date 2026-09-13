#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "number/factorize.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  int t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    auto f = factorize(n);
    int k = 0;
    for (auto [p, e] : f) k += e;
    cout << k << " ";
    for (auto [p, e] : f) {
      while (e--) cout << p << " ";
    }
    cout << "\n";
  }
}