#define PROBLEM "https://judge.yosupo.jp/problem/counting_squarefrees"

#include "number/count_square_free.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ll n;
  cin >> n;
  cout << count_square_free(n) << "\n";
}
