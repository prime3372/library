#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_5_A"

#include "tree/tree_diameter.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  tree_diameter<int> diam(n);
  for (int i = 0; i < n - 1; i++) {
    int s, t, w;
    cin >> s >> t >> w;
    diam.add_edge(s, t, w);
  }
  diam.build();
  cout << diam.dist << "\n";
}