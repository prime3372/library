#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull"

#include "geom/convex-hull.hpp"
#include "geom/point.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<Point<ll>> p(n);
    for (auto& pi : p) cin >> pi;
    auto ch = convex_hull(p);
    cout << ch.size() << "\n";
    for (auto& chi : ch) cout << chi << "\n";
  }
}