#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_2_C"
#define ERROR 1e-8

#include "geom/intersection.hpp"
#include "geom/line.hpp"
#include <iomanip>
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);
  int q;
  cin >> q;
  while (q--) {
    line<ll> l, m;
    cin >> l >> m;
    cout << intersection(l, m) << "\n";
  }
}