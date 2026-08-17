#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include "geom/point.hpp"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(0);
  int n;
  cin >> n;
  vector<point> ps(n);
  for (auto& p : ps) cin >> p;
  sort(ps.begin(), ps.end(),
      [](const point& lhs, const point& rhs) {
        int lo = lhs.ort(), ro = rhs.ort();
        if (lo > 2) lo -= 5;
        if (ro > 2) ro -= 5;
        if (lo != ro) return lo < ro;
        return lhs.cross(rhs) > 0;
  });
  for (auto& p : ps) cout << p << "\n";
}