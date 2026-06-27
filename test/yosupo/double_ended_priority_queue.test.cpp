#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"

#include "../../ds/double_ended_priority_queue.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  double_ended_priority_queue<int> pq;
  rep(i, 0, n) {
    int si;
    cin >> si;
    pq.push(si);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int x;
      cin >> x;
      pq.push(x);
    } else if (t == 1) {
      cout << pq.min() << "\n";
      pq.pop_min();
    } else {
      cout << pq.max() << "\n";
      pq.pop_max();
    }
  }
}
