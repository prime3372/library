#pragma once

#include <bits/stdc++.h>

#include "random/engine.hpp"
#include "util/algo_utility.hpp"
#include "util/io_float128.hpp"
#include "util/io_int128.hpp"
#include "util/io_utility.hpp"
#include "util/math_utility.hpp"
#include "util/static_modint.hpp"

#ifdef LOCAL
#define local 1
#else
#define local 0
#endif

#define __CHOOSE4(a, b, c, d, ...) d
#define __CHOOSE5(a, b, c, d, e, ...) e
#define __CHOOSE6(a, b, c, d, e, f, ...) f

#define rep1(n) for (ll _ = 0; _ < ll(n); _++)
#define rep2(i, n) for (ll i = 0; i < ll(n); i++)
#define rep3(i, a, b) for (ll i = (a); i < ll(b); i++)
#define rep4(i, a, b, c) for (ll i = (a); i < ll(b); i += (c))
#define rep(...) __CHOOSE5(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)

#define rrep2(i, n) for (ll i = ll(n) - 1; i >= 0; i--)
#define rrep3(i, a, b) for (ll i = ll(b) - 1; i >= ll(a); i--)
#define rrep(...) __CHOOSE4(__VA_ARGS__, rrep3, rrep2)(__VA_ARGS__)

#define REP2(i, n) for (ll i = 0; i <= ll(n); i++)
#define REP3(i, a, b) for (ll i = (a); i <= ll(b); i++)
#define REP4(i, a, b, c) for (ll i = (a); i <= ll(b); i += (c))
#define REP(...) __CHOOSE5(__VA_ARGS__, REP4, REP3, REP2)(__VA_ARGS__)

#define RREP2(i, n) for (ll i = (n); i >= 0; i--)
#define RREP3(i, a, b) for (ll i = (b); i >= ll(a); i--)
#define RREP(...) __CHOOSE4(__VA_ARGS__, RREP3, RREP2)(__VA_ARGS__)

#define fore2(x, a) for (auto&& x : a)
#define fore3(x, y, a) for (auto&& [x, y] : a)
#define fore4(x, y, z, a) for (auto&& [x, y, z] : a)
#define fore5(x, y, z, w, a) for (auto&& [x, y, z, w] : a)
#define fore(...) \
  __CHOOSE6(__VA_ARGS__, fore5, fore4, fore3, fore2)(__VA_ARGS__)

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

#ifdef LOCAL

#define dump(...)                               \
  [](const auto&... _args) {                    \
    std::string _args_str = #__VA_ARGS__;       \
    _args_str.append(": ");                     \
    std::cerr << _args_str;                     \
    std::string _indent(_args_str.size(), ' '); \
    std::ostringstream _oss;                    \
    _oss << std::make_tuple(_args...);          \
    for (char _c : _oss.str()) {                \
      std::cerr << _c;                          \
      if (_c == '\n') std::cerr << _indent;     \
    }                                           \
    std::cerr << "\n";                          \
  }(__VA_ARGS__)

#define msg(...) \
  [](const auto&... _args) -> void { (std::cerr << ... << _args); }(__VA_ARGS__)

#else

#define dump(...)
#define msg(...)

#endif

using uint = unsigned int;
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
using std::views::keys;
using std::views::values;
using std::views::zip;
using namespace std;

using mint = cp::modint998244353;
using namespace cp;

constexpr int INF = int(1e9);
constexpr ll LINF = (long long)(2e18);

template <class T> inline ll len(const T& a) { return a.size(); }

template <class T> inline bool chmin(T& a, const T& b) {
  return b < a ? (a = b, true) : false;
}

template <class T> inline bool chmax(T& a, const T& b) {
  return b > a ? (a = b, true) : false;
}

template <class T> inline T min(const std::vector<T>& v) {
  assert(!v.empty());
  return *std::min_element(v.begin(), v.end());
}

template <class T> inline T max(const std::vector<T>& v) {
  assert(!v.empty());
  return *std::max_element(v.begin(), v.end());
}

template <class T, class U, class F = std::plus<T>>
inline T accum(const std::vector<U>& v, U x, const F& f) {
  return std::accumulate(v.begin(), v.end(), x, f);
}

template <class Container,
          class Compare = std::less<std::ranges::range_value_t<Container>>>
inline int lower_bound(const Container& a,
                       std::ranges::range_value_t<Container> val,
                       Compare compare = Compare()) {
  return int(std::lower_bound(a.begin(), a.end(), val, compare) - a.begin());
}

template <class Container,
          class Compare = std::less<std::ranges::range_value_t<Container>>>
inline int upper_bound(const Container& a,
                       std::ranges::range_value_t<Container> val,
                       Compare compare = Compare()) {
  return int(std::upper_bound(a.begin(), a.end(), val, compare) - a.begin());
}

template <class T> inline bool inrange(const T& i, const T& a, const T& b) {
  return a <= i && i < b;
}