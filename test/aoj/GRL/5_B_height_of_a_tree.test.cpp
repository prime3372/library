#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_5_B"

#include "tree/rerooting_dp.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int op(int x, int y) { return max(x, y); }
int e() { return 0; }
int act(int f, int x) { return x + f; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  rerooting_dp<int, op, e, int, act> rerooting(n);
  for (int i = 0; i < n - 1; i++) {
    int s, t, w;
    cin >> s >> t >> w;
    rerooting.add_edge(s, t, w);
  }
  rerooting.build();
  for (int x : rerooting.ans) cout << x << "\n";
}