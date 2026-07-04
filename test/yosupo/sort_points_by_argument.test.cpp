#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include "geom/point.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(0);
  int n;
  cin >> n;
  vector<point> pts(n);
  rep(i, 0, n) cin >> pts[i];
  sort(pts.begin(), pts.end());
  rep(i, 0, n) cout << pts[i] << "\n";
}
