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
  auto factorized = factorize(n);
  string ans;
  for (auto f : factorized) {
    while (f.second--) {
      ans.append(std::to_string(f.first));
      ans.push_back(' ');
    }
  }
  ans.pop_back();
  cout << n << ": " << ans << "\n";
}