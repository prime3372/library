#pragma once

#include "util/io_utility.hpp"
#include "util/math_utility.hpp"
#include "util/static_modint.hpp"
using namespace cp;
using mint = modint998244353;

#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
template <class T> using vec = vector<T>;
template <class T> using pqueue = priority_queue<T, vector<T>, greater<T>>;

#define rep(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, a, b) for (int i = (a); i <= int(b); i++)
#define rrep(i, a, b) for (int i = int(b) - 1; i >= (a); i--)
#define RREP(i, a, b) for (int i = int(b); i >= (a); i--)
#define fore(x, a) for (auto& x : (a))
#define all(a) (a).begin(), (a).end()

#ifdef LOCAL

#define debug(...) \
  []<class... Args>(Args... args) { \
    (std::cerr << ... << args); \
  }(__VA_ARGS__)

#else

#define debug(...)

#endif