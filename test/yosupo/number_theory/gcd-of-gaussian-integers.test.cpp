#define PROBLEM "https://judge.yosupo.jp/problem/gcd_of_gaussian_integers"

#include "number/gaussian-integer.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;
using gint = GaussianInteger;

gint gcd(const gint& z1, const gint& z2) {
  return (z2.x == 0 && z2.y == 0) ? z1 : gcd(z2, z1 % z2);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    gint z1, z2;
    cin >> z1 >> z2;
    cout << gcd(z1, z2) << "\n";
  }
}