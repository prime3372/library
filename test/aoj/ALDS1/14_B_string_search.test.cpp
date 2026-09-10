#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"

#include "util/hash61.hpp"
#include "string/rolling_hash.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cp;

int main() {
  string t, p;
  cin >> t >> p;
  int n = int(t.size()), m = int(p.size());
  rolling_hash rlh(t);
  hash61 h = rolling_hash::to_hash(p);
  for (int i = 0; i <= n - m; i++) {
    if (rlh.get(i, i + m) == h) cout << i << "\n";
  }
}