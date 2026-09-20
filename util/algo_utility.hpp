#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <ranges>
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

// replace `a[i]` with `a[p[i]]` by `std::swap`
template <class Container, class Indices>
const Indices& rearrange(Container& a, const Indices& p) {
  assert(a.size() == p.size());
  std::vector<bool> processed(a.size());
  for (int i = 0; i < int(a.size()); i++) {
    if (processed[i]) continue;
    processed[i] = true;
    for (int j = p[i]; j != i; j = p[j]) {
      assert(!processed[j]);
      processed[j] = true;
      std::swap(a[j], a[p[j]]);
    }
  }
  return p;
}

template <class Container,
          class Compare = std::less<std::ranges::range_value_t<Container>>>
std::vector<int> sorted_indices(const Container& a,
                                Compare compare = Compare()) {
  std::vector<int> p(a.size());
  std::iota(p.begin(), p.end(), 0);
  std::sort(p.begin(), p.end(), [&](int i, int j) {
    return compare(a[i], a[j]) || (!compare(a[j], a[i]) && i < j);
  });
  return p;
}

template <class Container,
          class Compare = std::less<std::ranges::range_value_t<Container>>>
std::vector<int> sort(Container&& a, Compare compare = Compare()) {
  return rearrange(a, sorted_indices(a, compare));
}

template <class Container,
          class Compare = std::less<std::ranges::range_value_t<Container>>>
void sort_unique(Container& a, Compare compare = Compare()) {
  std::sort(a.begin(), a.end(), compare);
  a.erase(std::unique(a.begin(), a.end(),
                      [&](const auto& x, const auto& y) {
                        return !compare(x, y) && !compare(y, x);
                      }),
          a.end());
}

template <class Container,
          class Compare = std::less<std::ranges::range_value_t<Container>>>
std::vector<int> compress(Container a, Compare compare = Compare()) {
  int n = int(a.size());
  std::vector<int> res(n);
  auto p = sort(a, compare);
  for (int i = 0, j = 0; i < n; i++) {
    if (i > 0 && compare(a[i - 1], a[i])) j++;
    res[p[i]] = j;
  }
  return res;
}

template <class Container,
          class Compare = std::less<std::ranges::range_value_t<Container>>>
int lower_bound(const Container& a, std::ranges::range_value_t<Container> val,
                 Compare compare = Compare()) {
  return int(std::lower_bound(a.begin(), a.end(), val, compare) - a.begin());
}

template <class Container,
          class Compare = std::less<std::ranges::range_value_t<Container>>>
int upper_bound(const Container& a, std::ranges::range_value_t<Container> val,
                 Compare compare = Compare()) {
  return int(std::upper_bound(a.begin(), a.end(), val, compare) - a.begin());
}

template <class Container> Container inverse(const Container& p) {
  Container q(p.size());
  std::fill(q.begin(), q.end(), -1);
  for (int i = 0; i < int(p.size()); i++) {
    assert(0 <= p[i] && p[i] < int(p.size()));
    assert(q[p[i]] == -1);
    q[p[i]] = i;
  }
  return q;
}

}  // namespace cp