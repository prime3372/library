#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"

#include "string/suffix_array.hpp"
#include "string/lcp_array.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cp;

int main() {
  string s, t;
  cin >> s >> t;
  int n = int(s.size()), m = int(t.size());
  s.push_back('.');
  s += t;
  auto sa = suffix_array(s);
  auto lcp = lcp_array(s, sa);
  int max = 0, idx = -1;
  for (int i = 0; i < n + m + 1; i++) {
    bool different = (sa[i] < n) != (sa[i + 1] < n);
    if (different && max < lcp[i]) {
      max = lcp[i];
      idx = i;
    }
  }
  if (max == 0) {
    cout << 0 << " " << 0 << " " << 0 << " " << 0 << "\n";
  } else if (sa[idx] < n) {
    cout << sa[idx] << " " << sa[idx] + max << " ";
    cout << sa[idx + 1] - n - 1 << " " << sa[idx + 1] + max - n - 1 << "\n";
  } else {
    cout << sa[idx + 1] << " " << sa[idx + 1] + max << " ";
    cout << sa[idx] - n - 1 << " " << sa[idx] + max - n - 1 << "\n";
  }
}