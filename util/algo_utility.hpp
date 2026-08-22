#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

namespace cp {

template <class T> T min(const std::vector<T>& v) {
  assert(!v.empty());
  return *std::min_element(v.begin(), v.end());
}

template <class T> T max(const std::vector<T>& v) {
  assert(!v.empty());
  return *std::max_element(v.begin(), v.end());
}

template <class T> bool chmin(T& a, const T& b) {
  return b < a ? (a = b, true) : false;
}

template <class T> bool chmax(T& a, const T& b) {
  return b > a ? (a = b, true) : false;
}

template <class Container, class Comp>
std::vector<int> sort(Container& a, Comp comp) {
  std::vector<int> p(int(a.size()));
  std::iota(p.begin(), p.end(), 0);
  std::sort(p.begin(), p.end(), [&](int i, int j) { return comp(a[i], a[j]); });
  auto a2 = a;
  for (int i = 0; i < int(a.size()); i++) {
    a[i] = std::move(a2[p[i]]);
  }
  return p;
}

template <class Container> std::vector<int> sort(Container& a) {
  return sort(a, std::less<typename Container::value_type>());
}

template <class Container> void uniq(Container& a) {
  std::sort(a.begin(), a.end());
  a.erase(std::unique(a.begin(), a.end()), a.end());
}

}  // namespace cp