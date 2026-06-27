#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include "../../number/enumerate_primes.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, a, b;
  cin >> n >> a >> b;
  auto ps = enumerate_primes(n);
  vector<int> ans;
  for (int i = 0; a * i + b < int(ps.size()); i++) {
    ans.push_back(ps[a * i + b]);
  }
  cout << ps.size() << " " << ans.size() << "\n";
  rep(i, 0, ans.size()) {
    cout << ans[i] << " ";
  }
}
