#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_B"
#define ERROR 1e-8

#include "geom/line.hpp"
#include "geom/point.hpp"
#include "geom/reflection.hpp"
#include <iomanip>
#include <iostream>

using namespace std;
using namespace cp;
using ld = long double;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);
  Line<ld> l;
  int q;
  cin >> l >> q;
  while (q--) {
    Point<ld> p;
    cin >> p;
    cout << reflection(p, l) << "\n";
  }
}