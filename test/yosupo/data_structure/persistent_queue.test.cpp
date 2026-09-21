#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"

#include "ds/persistent_array.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  vector<int> l(q + 1), r(q + 1);
  vector<persistent_array<int>::node*> past(q + 1);
  persistent_array<int> s(q + 1);
  past[0] = s.snapshot();
  l[0] = r[0] = 0;
  for (int i = 1; i <= q; i++) {
    int type;
    cin >> type;
    if (type == 0) {
      int t, x;
      cin >> t >> x;
      t++;
      s.restore(past[t]);
      s.set(r[t], x);
      past[i] = s.snapshot();
      l[i] = l[t];
      r[i] = r[t] + 1;
    } else {
      int t;
      cin >> t;
      t++;
      s.restore(past[t]);
      cout << s[l[t]] << "\n";
      past[i] = past[t];
      l[i] = l[t] + 1;
      r[i] = r[t];
    }
  }
}