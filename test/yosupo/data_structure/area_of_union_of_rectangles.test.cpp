#define PROBLEM "https://judge.yosupo.jp/problem/area_of_union_of_rectangles"

#include "ds/area_of_union_of_rectangles.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  area_of_union_of_rectangles<ll> area;
  for (int i = 0; i < n; i++) {
    ll l, d, r, u;
    cin >> l >> d >> r >> u;
    area.add_rect(l, d, r, u);
  }
  cout << area.calc() << "\n";
}