#define PROBLEM "https://judge.yosupo.jp/problem/aho_corasick"

#include "string/aho_corasick.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  aho_corasick<26> aho;
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    v[i] = aho.insert(s);
  }
  aho.build();
  cout << aho.size() << "\n";
  for (int i = 1; i < aho.size(); i++) {
    cout << aho.parent(i) << " " << aho.link(i) << "\n";
  }
  for (int vi : v) cout << vi << " ";
}