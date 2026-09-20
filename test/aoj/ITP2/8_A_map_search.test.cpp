#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_8_A"

#include "ds/hash_map.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  hash_map<int, int> mp;
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int k, x;
      cin >> k >> x;
      mp[k] = x;
    } else {
      int k;
      cin >> k;
      cout << mp[k] << "\n";
    }
  }
}