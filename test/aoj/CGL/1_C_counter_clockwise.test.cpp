#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_C"

#include "geom/ccw.hpp"
#include "geom/point.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  point<ll> p0, p1;
  int q;
  cin >> p0 >> p1 >> q;
  while (q--) {
    point<ll> p2;
    cin >> p2;
    int c = ccw(p0, p1, p2);
    if (c == 1) {
      cout << "COUNTER_CLOCKWISE\n";
    } else if (c == -1) {
      cout << "CLOCKWISE\n";
    } else if (c == 2) {
      cout << "ONLINE_BACK\n";
    } else if (c == -2) {
      cout << "ONLINE_FRONT\n";
    } else {
      cout << "ON_SEGMENT\n";
    }
  }
}