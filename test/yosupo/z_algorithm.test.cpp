#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../string/z_algorithm.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  auto z = z_algorithm(s);
  for (int i : z) cout << i << " ";
}
