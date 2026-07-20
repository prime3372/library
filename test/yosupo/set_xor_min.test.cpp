#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include "ds/binary_trie.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  binary_trie<unsigned int> trie;
  while (q--) {
    int t;
    unsigned int x;
    cin >> t >> x;
    if (t == 0) {
      if (trie.count(x) == 0) trie.insert(x);      
    } else if (t == 1) {
      trie.erase(x);
    } else {
      unsigned int m = 0;
      int v = 0;
      for (int i = 31; i >= 0; i--) {
        bool b = (x >> i) & 1;
        m <<= 1;
        if (trie[v][b] != -1) {
          v = trie[v][b];
        } else {
          v = trie[v][!b];
          m++;
        }
      }
      cout << m << "\n";
    }
  }
}