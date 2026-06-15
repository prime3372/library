#define PROBLEM "https://judge.yosupo.jp/problem/counting_squarefrees"

#include "../../number/count_square_free.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

int main() {
  ll n;
  cin >> n;
  cout << count_square_free(n) << "\n";
}
