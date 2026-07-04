#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"

#include "util/int128.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    __int128 x, y;
    cin >> x >> y;
    cout << x + y << "\n";
  }
}