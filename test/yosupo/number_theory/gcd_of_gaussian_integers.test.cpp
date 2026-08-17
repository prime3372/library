#define PROBLEM "https://judge.yosupo.jp/problem/gcd_of_gaussian_integers"

#include "number/gcd_of_gaussian_integers.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;
using gint = gaussian_integer;

int main() {
  int t;
  cin >> t;
  while (t--) {
    gint z1, z2;
    cin >> z1 >> z2;
    cout << gcd_of_gaussian_integers(z1, z2) << "\n";
  }
}