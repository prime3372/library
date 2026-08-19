#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include "geom/ipoint.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(0);
  int n;
  cin >> n;
  vector<ipoint> ps(n);
  for (auto& p : ps) cin >> p;
  sort(ps.begin(), ps.end(), [](const ipoint& lhs, const ipoint& rhs) {
    if (lhs.x < 0 && lhs.y == 0) return false;
    if (rhs.x < 0 && rhs.y == 0) return true;
    int lo = lhs.ort(), ro = rhs.ort();
    if (lo >= 3) lo -= 5;
    if (ro >= 3) ro -= 5;
    if (lo != ro) return lo < ro;
    return cross(lhs, rhs) > 0;
  });
  for (auto& p : ps) cout << p << "\n";
}