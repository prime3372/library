#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_A"

#include "number/factorize.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cp;

int main() {
  int n;
  cin >> n;
  auto f = factorize(n);
  string ans;
  for (auto [p, e] : f) {
    while (e--) {
      ans.append(to_string(p));
      ans.push_back(' ');
    }
  }
  ans.pop_back();
  cout << n << ": " << ans << "\n";
}