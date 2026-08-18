#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_5_B"

#include "algebra/max_add.hpp"
#include "tree/rerooting_dp.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  rerooting_dp<alg::max_add<int, 0>> rerooting(n);
  for (int i = 0; i < n - 1; i++) {
    int s, t, w;
    cin >> s >> t >> w;
    rerooting.add_edge(s, t, w);
  }
  rerooting.build();
  for (int i = 0; i < n; i++) cout << rerooting.ans[i] << "\n";
}