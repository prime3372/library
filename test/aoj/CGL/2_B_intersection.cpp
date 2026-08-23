#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_2_B"

#include "geom/intersect.hpp"
#include "geom/segment.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  while (q--) {
    segment<ll> l, m;
    cin >> l >> m;
    cout << intersect(l, m) << "\n";
  }
}