#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_8_A"

#include "ds/hash_map.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  hash_map<string, int> mp;
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      string k;
      int x;
      cin >> k >> x;
      mp[k] = x;
    } else {
      string k;
      cin >> k;
      cout << mp[k] << "\n";
    }
  }
}