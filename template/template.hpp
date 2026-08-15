#pragma once

// All the remaining parts of this library works without this template.

#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
template <class T> using vec = vector<T>;
using str = string;
template <class T> using pque = priority_queue<T, vector<T>, greater<T>>;

#ifdef LOCAL

#define iflocal if (true)
#define ifnlocal if (false)
#define debug(...) \
  []<class... Args>(Args... args) { \
    (std::cerr << ... << args); \
    std::cerr << "\n"; \
  }(__VA_ARGS__)

#else

#define iflocal if (false)
#define ifnlocal if (true)
#define debug(...)

#endif

#define rep(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, a, b) for (int i = (a); i <= int(b); i++)
#define rrep(i, a, b) for (int i = int(b) - 1; i >= (a); i--)
#define RREP(i, a, b) for (int i = int(b); i >= (a); i--)
#define fore(x, a) for (auto& x : (a))
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

#include "util/algo_utility.hpp"
#include "util/io_utility.hpp"
#include "util/math_utility.hpp"
#include "util/static_modint.hpp"
using namespace cp;
using mint = modint998244353;