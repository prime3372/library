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
    auto factorized = factorize(n);
    int k = 0;
    for (auto& f : factorized) k += f.second;
    cout << k << " ";
    for (auto& f : factorized) {
      while (f.second--) cout << f.first << " ";
    }
    cout << "\n";
  }
}