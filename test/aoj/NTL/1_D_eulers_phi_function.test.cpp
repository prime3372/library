#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_D"

#include "number/totient.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ll n;
  cin >> n;
  cout << totient(n) << "\n";
}