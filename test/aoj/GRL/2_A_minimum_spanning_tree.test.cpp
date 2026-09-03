#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_2_A"

#include "graph/kruscal.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  kruscal<int> g(n);
  for (int i = 0; i < m; i++) {
    int s, t, w;
    cin >> s >> t >> w;
    g.add_edge(s, t, w);
  }
  cout << g.min() << "\n";
}