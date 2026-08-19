#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_D"

#include "number/factorize.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ll n;
  cin >> n;
  auto fac = factorize(n);
  for (auto& f : fac) {
    n /= f.first;
    n *= (f.first - 1);
  }
  cout << n << "\n";
}