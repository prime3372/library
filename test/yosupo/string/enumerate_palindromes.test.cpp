#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include "string/manacher.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  auto ans = manacher(s);
  for (int x : ans) cout << x << " ";
}