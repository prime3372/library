#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"

#include "../../util/int128.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;

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
