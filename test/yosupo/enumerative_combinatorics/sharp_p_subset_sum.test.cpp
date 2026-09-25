#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include "poly/formal_power_series.hpp"
#include "poly/exp_of_formal_power_series.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;
constexpr int m = 998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, t;
  cin >> n >> t;
  vector<int> s(n);
  for (int& x : s) cin >> x;
  vector<int> cnt(t + 1);
  for (int x : s) cnt[x]++;
  vector<mint> minv(t + 1);
  minv[1] = 1;
  for (int i = 2; i <= t; i++) {
    minv[i] = -minv[m % i] * (m / i);
  }
  formal_power_series<mint> f(t + 1);
  for (int i = 1; i <= t; i++) {
    for (int j = 1; i * j <= t; j++) {
      f[i * j] += cnt[i] * (j % 2 ? 1 : -1) * minv[j];
    }
  }
  auto g = exp(f);
  for (int i = 1; i <= t; i++) cout << g[i] << " ";
}