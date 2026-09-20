#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"

#include "string/suffix_array.hpp"
#include "string/lcp_array.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s, t;
  cin >> s >> t;
  int n = int(s.size()), m = int(t.size());
  s.push_back(-1);
  s.append(t);
  auto sa = suffix_array(s);
  auto lcp = lcp_array(s, sa);
  int max = 0, p = -1;
  for (int i = 0; i < n + m + 1; i++) {
    if ((sa[i] < n) == (sa[i + 1] < n)) continue;
    if (lcp[i] > max) {
      max = lcp[i];
      p = i;
    }
  }
  if (max == 0) {
    cout << 0 << " " << 0 << " " << 0 << " " << 0 << "\n";
  } else if (sa[p] < n) {
    cout << sa[p] << " " << sa[p] + max << " ";
    cout << sa[p + 1] - n - 1 << " " << sa[p + 1] + max - n - 1 << "\n";
  } else {
    cout << sa[p + 1] << " " << sa[p + 1] + max << " ";
    cout << sa[p] - n - 1 << " " << sa[p] + max - n - 1 << "\n";
  }
}