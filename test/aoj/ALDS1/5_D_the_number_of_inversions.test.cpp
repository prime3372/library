#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_5_D"

#include "util/inversion.hpp"
#include <vector>

using namespace std;
using namespace cp;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int& x : a) cin >> x;
  cout << inversion(a) << "\n";
}