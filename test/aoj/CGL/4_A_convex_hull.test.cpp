#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_4_A"

#include "geom/convex_hull.hpp"
#include "geom/point.hpp"
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(1);
  int n;
  cin >> n;
  vector<point<ll>> p(n);
  for (auto& pi : p) cin >> pi;
  auto ch = convex_hull<true>(p);
  int m = int(ch.size()), j = 0;
  while (j < m && ch[j].y > ch[j + 1].y) j++;
  cout << m << "\n";
  cout << ch[j] << "\n";
  for (int i = j + 1; i != j; i = (i + 1) % m) {
    cout << ch[i] << "\n";
  }
}