#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_7_B"

#include "ds/hash_set.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  hash_set<int> s;
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int x;
      cin >> x;
      s.insert(x);
      cout << s.size() << "\n";
    } else if (t == 1) {
      int x;
      cin >> x;
      cout << s.count(x) << "\n";
    } else {
      int x;
      cin >> x;
      s.erase(x);
    }
  }
}