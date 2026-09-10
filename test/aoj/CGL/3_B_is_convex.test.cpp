#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_B"

#include "geom/is_convex.hpp"
#include "geom/point.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<point<ll>> p(n);
  for (int i = 0; i < n; i++) cin >> p[i];
  cout << is_convex(p) << "\n";
}