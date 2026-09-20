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
using std::views::zip;

using namespace cp;
using mint = cp::modint998244353;

#ifdef LOCAL
#define local 1
#else
#define local 0
#endif

#define CHOOSE4(a, b, c, d, ...) d
#define rep1(n) for (ll _ = 0; _ < ll(n); _++)
#define rep2(i, n) for (ll i = 0; i < ll(n); i++)
#define rep3(i, a, b) for (ll i = (a); i < ll(b); i++)
#define rep(...) CHOOSE4(__VA_ARGS__, rep3, rep2, rep1)(__VA_ARGS__)

#define rrep(i, a, b) for (ll i = ll(b) - 1; i >= ll(a); i--)
#define REP(i, a, b) for (ll i = (a); i <= ll(b); i++)
#define RREP(i, a, b) for (ll i = ll(b) - 1; i >= ll(a); i--)

#define CHOOSE6(a, b, c, d, e, f, ...) f
#define fore2(x, a) for (auto&& x : a)
#define fore3(x, y, a) for (auto&& [x, y] : a)
#define fore4(x, y, z, a) for (auto&& [x, y, z] : a)
#define fore5(x, y, z, w, a) for (auto&& [x, y, z, w] : a)
#define fore(...) CHOOSE6(__VA_ARGS__, fore5, fore4, fore3, fore2)(__VA_ARGS__)

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

#define inrange(i, a, b) ((a) <= (i) && (i) < (b))

constexpr int INF = int(1e9);
constexpr ll LINF = ll(2e18);

template <class T> inline int len(const T& a) { return int(a.size()); }