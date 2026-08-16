#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/1/DPL_1_D"

#include "util/length_of_lis.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int& ai : a) cin >> ai;
  cout << length_of_lis(a) << "\n";
}