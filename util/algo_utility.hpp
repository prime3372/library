#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <type_traits>
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

// a[i] <- a[p[i]]
// @param p must be a permutation
template <class Container, class Indices>
void rearrange(Container& a, const Indices& p) {
  assert(a.size() == p.size());
  Container b = a;
  for (int i = 0; i < int(p.size()); i++) {
    a[i] = std::move(b[p[i]]);
  }
}

// stable sort
// @return let `b` be the sorted array, return `p` s.t. `b[i] = a[p[i]]`.
template <class Container,
          class Comp = std::less<typename std::decay_t<Container>::value_type>>
std::vector<int> sort(Container&& a, Comp comp = Comp()) {
  std::vector<int> p(a.size());
  std::iota(p.begin(), p.end(), 0);
  std::sort(p.begin(), p.end(), [&](int i, int j) {
    return comp(a[i], a[j]) || (!comp(a[j], a[i]) && i < j);
  });
  rearrange(a, p);
  return p;
}

template <class Container,
          class Comp = std::less<typename Container::value_type>>
void uniq(Container& a, Comp comp = Comp()) {
  std::sort(a.begin(), a.end(), comp);
  a.erase(std::unique(a.begin(), a.end(),
                      [&](const auto& x, const auto& y) {
                        return !comp(x, y) && !comp(y, x);
                      }),
          a.end());
}

template <class Container,
          class Comp = std::less<typename Container::value_type>>
std::vector<int> compress(const Container& a, Comp comp = Comp()) {
  int n = int(a.size());
  Container b = a;
  auto idx = sort(b, comp);
  std::vector<int> res(n);
  for (int i = 0, j = 0; i < n; i++) {
    if (i > 0 && comp(b[i - 1], b[i])) j++;
    res[idx[i]] = j;
  }
  return res;
}

}  // namespace cp