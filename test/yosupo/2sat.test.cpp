#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"

#include "../../graph/two_sat.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  {
    string dummy;
    cin >> dummy >> dummy;
  }
  int n, m;
  cin >> n >> m;
  two_sat sat(n);
  rep(i, 0, m) {
    int a, b, dummy;
    cin >> a >> b >> dummy;
    bool f = a > 0, g = b > 0;
    a = abs(a) - 1;
    b = abs(b) - 1;
    sat.add_clause(a, f, b, g);
  }
  auto ans = sat.solve();
  if (ans.empty()) {
    cout << "s UNSATISFIABLE\n";
    return 0;
  }
  cout << "s SATISFIABLE\n";
  cout << "v ";
  rep(i, 0, ans.size()) {
    cout << (ans[i] ? i + 1: -i - 1) << " ";
  }
  cout << "0\n";
}
