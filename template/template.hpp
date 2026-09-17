#pragma once

#include <bits/stdc++.h>

#include "random/engine.hpp"
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

#define CHOOSE5(_1, _2, _3, _4, name, ...) name
#define CHOOSE6(_1, _2, _3, _4, _5, name, ...) name

#define rep1(n) for (ll _ = 0; _ < ll(n); _++)
#define rep2(i, n) for (ll i = 0; i < ll(n); i++)
#define rep3(i, a, b) for (ll i = (a); i < ll(b); i++)
#define rep4(i, a, b, c) for (ll i = (a); i < ll(b); i += (c))
#define rep(...) CHOOSE5(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)

#define REP2(i, n) for (ll i = 0; i <= ll(n); i++)
#define REP3(i, a, b) for (ll i = (a); i <= ll(b); i++)
#define REP4(i, a, b, c) for (ll i = (a); i <= ll(b); i += (c))
#define REP(...) CHOOSE5(__VA_ARGS__, REP4, REP3, REP2)(__VA_ARGS__)

#define rrep2(i, n) for (ll i = ll(n) - 1; i >= 0; i--)
#define rrep3(i, a, b) for (ll i = ll(b) - 1; i >= ll(a); i--)
#define rrep4(i, a, b, c) for (ll i = ll(b) - 1; i >= ll(a); i -= (c))
#define rrep(...) CHOOSE5(__VA_ARGS__, rrep4, rrep3, rrep2)(__VA_ARGS__)

#define fore2(x, a) for (auto&& x : (a))
#define fore3(x, y, a) for (auto&& [x, y] : (a))
#define fore4(x, y, z, a) for (auto&& [x, y, z] : (a))
#define fore5(x, y, z, w, a) for (auto&& [x, y, z, w] : (a))
#define fore(...) CHOOSE6(__VA_ARGS__, fore5, fore4, fore3, fore2)(__VA_ARGS__)

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

template <class T> bool inrange(T i, T a, T b) { return a <= i && i < b; }
template <class Container> int len(const Container& a) { return int(a.size()); }

#define GET_STRING_SINGLE(a) #a
#define GET_STRING(...)                                \
  []() {                                               \
    std::string _s = GET_STRING_SINGLE((__VA_ARGS__)); \
    return _s.substr(1, _s.size() - 2);                \
  }()

#ifdef LOCAL

#define local 1

#define dump(...)                                    \
  [](const auto&... _args) {                         \
    std::string _args_str = GET_STRING(__VA_ARGS__); \
    _args_str.append(": ");                          \
    std::cerr << _args_str;                          \
    std::string _indent(_args_str.size(), ' ');      \
    std::ostringstream _oss;                         \
    _oss << std::make_tuple(_args...);               \
    for (char _c : _oss.str()) {                     \
      std::cerr << _c;                               \
      if (_c == '\n') std::cerr << _indent;          \
    }                                                \
    std::cerr << "\n";                               \
  }(__VA_ARGS__)
#define write(...) \
  [](const auto&... _args) -> void { (std::cerr << ... << _args); }(__VA_ARGS__)

#else

#define local 0

#define dump(...)
#define write(...)

#endif