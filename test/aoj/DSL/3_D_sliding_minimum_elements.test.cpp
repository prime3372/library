#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_3_D"

#include "algebra/min.hpp"
#include "ds/slide_window_aggregation.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using M = alg::min<int, int(1e9) + 1>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, l;
  cin >> n >> l;
  slide_window_aggregation<M> swag;
  for (int i = 0; i < l; i++) {
    int a;
    cin >> a;
    swag.push(a);
  }
  cout << swag.prod();
  if (l != n) cout << " ";
  for (int i = 0; i < n - l; i++) {
    int a;
    cin >> a;
    swag.push(a);
    swag.pop();
    cout << swag.prod();
    if (i != n - l - 1) cout << " ";
  }
  cout << "\n";
}