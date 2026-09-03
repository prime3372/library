#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_B"
#define ERROR 1e-8

#include "geom/line.hpp"
#include "geom/point.hpp"
#include "geom/reflection.hpp"
#include <iomanip>
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);
  line<ll> l;
  int q;
  cin >> l >> q;
  while (q--) {
    point<ll> p;
    cin >> p;
    cout << reflection(p, l) << "\n";
  }
}