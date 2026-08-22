#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_2_A"

#include "geom/line.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  while (q--) {
    iline l, m;
    cin >> l >> m;
    if (is_parallel(l, m)) {
      cout << 2 << "\n";
    } else if (is_orthogonal(l, m)) {
      cout << 1 << "\n";
    } else {
      cout << 0 << "\n";
    }
  }
}