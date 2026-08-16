#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"

#include "ds/priority_deque.hpp"

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  priority_deque<int> pq;
  for (int i = 0; i < n; i++) {
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