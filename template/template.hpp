#pragma once

#include <bits/stdc++.h>

#include "random/engine.hpp"
#include "template/debug.hpp"
#include "util/algo_utility.hpp"
#include "util/io_float128.hpp"
#include "util/io_int128.hpp"
#include "util/io_utility.hpp"
#include "util/math_utility.hpp"
#include "util/static_modint.hpp"

using namespace std;
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
#if __cplusplus >= 202302L
using std::views::zip;
#endif

using namespace cp;
using mint = cp::modint998244353;

#ifdef LOCAL
#define local 1
#else
#define local 0
#endif

#define rep(i, a, b) for (ll i = (a); i < ll(b); i++)
#define REP(i, a, b) for (ll i = (a); i <= ll(b); i++)
#define rrep(i, a, b) for (ll i = ll(b) - 1; i >= ll(a); i--)
#define RREP(i, a, b) for (ll i = (b); i >= ll(a); i--)
#define fore(x, a) for (auto&& x : a)

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

#define inrange(i, a, b) ((a) <= (i) && (i) < (b))

constexpr int INF = int(1e9);
constexpr ll LINF = ll(1e18);

template <class T> inline int len(const T& a) { return int(a.size()); }