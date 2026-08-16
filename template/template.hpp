#pragma once

#include <bits/stdc++.h>

#include "random/base.hpp"
#include "util/algo_utility.hpp"
#include "util/io_utility.hpp"
#include "util/math_utility.hpp"
#include "util/static_modint.hpp"

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
template <class T> using vec = vector<T>;
using str = string;
template <class T> using minque = priority_queue<T, vector<T>, greater<T>>;
template <class T> using maxque = priority_queue<T>;

using namespace cp;
using mint = modint998244353;

#ifdef LOCAL

#define iflocal if (true)
#define ifnlocal if (false)
#define debug(...) \
  []<class... _Debug>(const _Debug&... _debug) { \
    (std::cerr << ... << _debug); \
    std::cerr << "\n"; \
  }(__VA_ARGS__)

#else

#define iflocal if (false)
#define ifnlocal if (true)
#define debug(...)

#endif

#define rep(i, a, b) for (ll i = (a); i < ll(b); i++)
#define REP(i, a, b) for (ll i = (a); i <= ll(b); i++)
#define rrep(i, a, b) for (ll i = ll(b) - 1; i >= (a); i--)
#define RREP(i, a, b) for (ll i = ll(b); i >= (a); i--)
#define fore(x, a) for (auto& x : (a))
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()