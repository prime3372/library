#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_2_B"

#include "geom/intersect.hpp"
#include "geom/segment.hpp"
#include <iomanip>
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);
  int q;
  cin >> q;
  while (q--) {
    isegment l, m;
    cin >> l >> m;
    cout << intersect(l, m) << "\n";
  }
}