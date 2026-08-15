#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_3_D"

#include "algebra/min.hpp"
#include "ds/slide_window_aggregation.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < int(b); i++)
using namespace std;
using namespace cp;
using M = alg::min<int, int(1e9) + 1>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, l;
  cin >> n >> l;
  slide_window_aggregation<M> swag;
  rep(i, 0, l) {
    int a;
    cin >> a;
    swag.push(a);
  }
  cout << swag.prod();
  if (l != n) cout << " ";
  rep(i, 0, n - l) {
    int a;
    cin >> a;
    swag.push(a);
    swag.pop();
    cout << swag.prod();
    if (i != n - l - 1) cout << " ";
  }
  cout << "\n";
}