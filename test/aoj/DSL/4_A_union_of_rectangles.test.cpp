#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/4/DSL_4_A"

#include "ds/area_of_union_of_rectangles.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  int n;
  cin >> n;
  area_of_union_of_rectangles<ll> area;
  for (int i = 0; i < n; i++) {
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    area.add_rect(x1, y1, x2, y2);
  }
  cout << area.calc() << "\n";
}