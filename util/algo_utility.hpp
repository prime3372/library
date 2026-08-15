#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

namespace cp {

template <class T> bool chmin(T& a, const T& b) {
  return b < a ? (a = b, true) : false;
}

template <class T> bool chmax(T& a, const T& b) {
  return b > a ? (a = b, true) : false;
}

template <class T> auto min_elem(const T& a) {
  assert(!a.empty());
  return *std::min_element(a.begin(), a.end());
}

template <class T> auto max_elem(const T& a) {
  assert(!a.empty());
  return *std::max_element(a.begin(), a.end());
}

template <class T = long long, class U>
T sum(const U& a) {
  return std::accumulate(a.begin(), a.end(), T(0));
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

}