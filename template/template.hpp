#pragma once

#include <bits/stdc++.h>

#include "random/base.hpp"
#include "util/algo_utility.hpp"
#include "util/io_float128.hpp"
#include "util/io_int128.hpp"
#include "util/io_utility.hpp"
#include "util/math_utility.hpp"
#include "util/static_modint.hpp"

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;
template <class T> using vec = std::vector<T>;
using str = std::string;
template <class T>
using minque = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <class T> using maxque = std::priority_queue<T>;

using namespace cp;
using mint = cp::modint998244353;

#ifdef LOCAL

#define GET_STRING(a, ...) #a

#define local 1
#define dump(...)                                                        \
  []<class... _Args>(const _Args&... _args) -> void {                    \
    std::string _args_str = GET_STRING((__VA_ARGS__));                   \
    if (sizeof...(_Args) <= 1)                                           \
      _args_str = _args_str.substr(1, _args_str.size() - 2);             \
    std::cerr << _args_str << ": " << std::make_tuple(_args...) << "\n"; \
  }(__VA_ARGS__)
#define write(...) \
  [](const auto&... _args) -> void { (cerr << ... << _args); }(__VA_ARGS__)

#else

#define local 0
#define dump(...)
#define write(...)

#endif

#define rep(i, a, b) for (ll i = ll(a); i < ll(b); i++)
#define REP(i, a, b) for (ll i = ll(a); i <= ll(b); i++)
#define rrep(i, a, b) for (ll i = ll(b) - 1; i >= ll(a); i--)
#define RREP(i, a, b) for (ll i = ll(b); i >= ll(a); i--)
#define fore(x, a) for (auto&& x : (a))
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()