#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>

namespace cp {

template <class T = long long>
T ipow(long long x, long long n) {
  assert(0 <= n);
  T r = 1, t = x;
  while (n) {
    if (n & 1) r *= t;
    t *= t;
    n >>= 1;
  }
  return r;
}

template <class T> T isqrt(T x) {
  T y = T(std::sqrt(double(x)));
  if (sizeof(T) > 8) {
    y = (y + x / y) / 2; // Newton's method
  }
  while (y != 0 && y > x / y) y--;
  while ((y + 1) <= x / (y + 1)) y++;
  return y;
}

template <class T> T icbrt(T x) {
  T y = T(std::cbrt(double(x)));
  while (y != 0 && y * y > x / y) y--;
  while ((y + 1) * (y + 1) <= x / (y + 1)) y++;
  return y;
}

template <class T> bool chmin(T& a, T b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}

template <class T> bool chmax(T& a, T b) {
  if (b > a) {
    a = b;
    return true;
  }
  return false;
}

template <class T> auto min(const T& a) {
  assert(!a.empty());
  return *std::min_element(a.begin(), a.end());
}

template <class T> auto max(const T& a) {
  assert(!a.empty());
  return *std::max_element(a.begin(), a.end());
}

template <class T> long long sum(const T& a) {
  return std::accumulate(a.begin(), a.end(), 0LL);
}

template <class T> void uniq(T& a) {
  std::sort(a.begin(), a.end());
  a.erase(std::unique(a.begin(), a.end()), a.end());
}

template <bool descending = false, class... Args>
std::vector<int> zip_sort(Args&... args) {
  if (sizeof...(Args) == 0) return {};

  int n = int(std::get<0>(std::tie(args...)).size());
  assert(((int(args.size()) == n) && ...));

  std::vector<int> p(n);
  std::iota(p.begin(), p.end(), 0);
  std::sort(p.begin(), p.end(), [&](int i, int j) {
    if (descending) return std::tie(args[i]...) > std::tie(args[j]...);
    else return std::tie(args[i]...) < std::tie(args[j]...);
  });

  ([&](auto& arg) {
    auto tmp = arg;
    for (int i = 0; i < n; i++) {
      arg[i] = std::move(tmp[p[i]]);
    }
  }(args), ...);
  return p;
}

} // namespace cp