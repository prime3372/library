#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include "ds/binary_trie.hpp"
#include <bitset>
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  binary_trie<30> trie;
  while (q--) {
    int t;
    unsigned int s;
    cin >> t >> s;
    if (t == 0) {
      if (trie.count(s) == 0) trie.insert(s);
    } else if (t == 1) {
      trie.erase(s);
    } else {
      cout << trie.min(s).to_ullong() << "\n";
    }
  }
}