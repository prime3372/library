#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include "ds/binary_trie.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  binary_trie<unsigned int> tr;
  while (q--) {
    int t;
    unsigned int x;
    cin >> t >> x;
    if (t == 0) {
      if (tr.count(x) == 0) tr.insert(x);
    } else if (t == 1) {
      tr.erase(x);
    } else {
      unsigned int ans = 0;
      int v = 0;
      for (int i = 31; i >= 0; i--) {
        bool b = (x >> i) & 1;
        if (tr[v][b] != -1) {
          v = tr[v][b];
        } else {
          v = tr[v][!b];
          ans |= 1U << i;
        }
      }
      cout << ans << "\n";
    }
  }
}