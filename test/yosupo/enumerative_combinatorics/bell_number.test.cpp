#define PROBLEM "https://judge.yosupo.jp/problem/bell_number"

#include "comb/bell.hpp"
#include "util/static_modint.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  int n;
  cin >> n;
  auto a = bell<mint>(n);
  for (int i = 0; i <= n; i++) cout << a[i] << " ";
}