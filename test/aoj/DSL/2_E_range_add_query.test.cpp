#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_E"

#include "ds/range_add_point_get.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  range_add_point_get<int> data(n + 1);
  while (q--) {
    int com;
    cin >> com;
    if (com == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      data.add(s - 1, t, x);
    } else {
      int i;
      cin >> i;
      cout << data[i - 1] << "\n";
    }
  }
}