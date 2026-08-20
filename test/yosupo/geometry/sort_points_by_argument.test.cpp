#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include "geom/point.hpp"
#include "geom/argument_sort.hpp"
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
  argument_sort(ps);
  for (auto& p : ps) cout << p << "\n";
}