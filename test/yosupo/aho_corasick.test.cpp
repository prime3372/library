#define PROBLEM "https://judge.yosupo.jp/problem/aho_corasick"

#include "string/aho_corasick.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  aho_corasick<false> aho;
  std::vector<int> v(n);
  rep(i, 0, n) {
    string s;
    cin >> s;
    v[i] = aho.insert(s);
  }
  aho.build();
  cout << aho.size() << "\n";
  rep(i, 1, aho.size()) {
    cout << aho.parent(i) << " " << aho.link(i) << "\n";
  }
  rep(i, 0, n) cout << v[i] << " ";
}