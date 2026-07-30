#include <bits/stdc++.h>
#include "util/ios_overload.hpp"
#include "util/static_modint.hpp"
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
#define REP(i, a, b) for (int i = int(a); i <= int(b); i++)
#define all(a) a.begin(), a.end()
using namespace std;
using namespace cp;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
using mint = modint998244353;
template <class T> using vec = vector<T>;
template <class T> bool chmin(T& a, T b) { if (b < a) { a = b; return 1; } else return 0; }
template <class T> bool chmax(T& a, T b) { if (b > a) { a = b; return 1; } else return 0; }
i128 ipow(i128 x, i128 n) {
  assert(0 <= n);
  i128 r = 1;
  while (n) { if (n & 1) r *= x; x *= x; n >>= 1; }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}