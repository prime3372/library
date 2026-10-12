#define PROBLEM "https://judge.yosupo.jp/problem/AreaOfUnionOfRectangles"

#include "ds/area-of-union-of-rectangles.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  AreaOfUnionOfRectangles<ll> area;
  for (int i = 0; i < n; i++) {
    ll l, d, r, u;
    cin >> l >> d >> r >> u;
    area.add_rect(l, d, r, u);
  }
  cout << area.calc() << "\n";
}