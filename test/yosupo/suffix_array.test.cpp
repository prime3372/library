#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../../string/suffix_array.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  auto sa = suffix_array(s);
  rep(i, 1, sa.size()) {
    cout << sa[i] << " ";
  }
}
