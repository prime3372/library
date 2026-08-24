#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_A"

#include "number/factorize.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cp;

int main() {
  int n;
  cin >> n;
  auto fac = factorize(n);
  string ans;
  for (auto f : fac) {
    while (f.second--) {
      ans.append(std::to_string(f.first));
      ans.push_back(' ');
    }
  }
  ans.pop_back();
  cout << n << ": " << ans << "\n";
}