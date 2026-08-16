#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "string/z_algorithm.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  auto z = z_algorithm(s);
  for (int i : z) cout << i << " ";
}