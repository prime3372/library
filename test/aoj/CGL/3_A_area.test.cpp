#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_A"

#include "geom/area.hpp"
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
  vector<point<ll>> ps(n);
  for (auto& p : ps) cin >> p;
  cout << area(ps) << "\n";
}