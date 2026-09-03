#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_2_D"
#define ERROR 1e-8

#include "geom/dist.hpp"
#include "geom/segment.hpp"
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
    segment<ll> l, m;
    cin >> l >> m;
    cout << dist(l, m) << "\n";
  }
}