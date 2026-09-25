#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include "number/partition.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  auto p = partition<mint>(n);
  for (mint& x : p) cout << x << " ";
}