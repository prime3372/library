#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"

#include "comb/monmort.hpp"
#include "util/dynamic_modint.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  modint::set_mod(m);
  auto a = monmort<modint>(n);
  for (int i = 1; i <= n; i++) cout << a[i] << " ";
}