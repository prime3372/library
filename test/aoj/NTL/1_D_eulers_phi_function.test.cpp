#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_D"

#include "number/factorize.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ll n;
  cin >> n;
  for (auto [p, e] : factorize(n)) {
    n /= p;
    n *= (p - 1);
  }
  return n;
}