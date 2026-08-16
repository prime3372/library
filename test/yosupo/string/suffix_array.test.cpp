#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "string/suffix_array.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  auto sa = suffix_array(s);
  for (int i = 1; i < int(sa.size()); i++) cout << sa[i] << " ";
}