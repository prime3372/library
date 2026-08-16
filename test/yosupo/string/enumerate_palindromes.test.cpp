#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include "string/rolling_hash.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  rolling_hash rlh(s);
  int n = int(s.size());
  reverse(s.begin(), s.end());
  rolling_hash rrlh(s);
  for (int i = 0; i < 2 * n - 1; i++) {
    int l = 0, r = n;
    while (r - l > 1) {
      int mid = (l + r) / 2, p = (i + 1) / 2, q = p + (i % 2 == 0);
      if (p - mid < 0 || n - q - mid < 0) {
        r = mid;
        continue; 
      }
      if (rlh.get(p - mid, p) == rrlh.get(n - q - mid, n - q)) l = mid;
      else r = mid;        
    }
    cout << 2 * l + (i % 2 == 0) << " ";
  }
}