#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_4_A"

#include "graph/cycle_detection.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  cycle_detection<true> cycle(n);
  for (int i = 0; i < m; i++) {
    int s, t;
    cin >> s >> t;
    cycle.add_edge(s, t);
  }
  cycle.detect();
  cout << (cycle.len != 0) << "\n";
}