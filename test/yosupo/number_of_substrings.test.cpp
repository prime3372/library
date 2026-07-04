#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include "string/lcp_array.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  ll n = s.size();
  auto lcp = lcp_array(s);
  cout << n * (n + 1) / 2 - std::accumulate(lcp.begin(), lcp.end(), 0LL) << "\n";
}
