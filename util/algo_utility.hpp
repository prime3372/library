#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <numeric>
#include <ranges>
#include <vector>

namespace cp {

// replace `a[i]` with `a[p[i]]` by the minimum number of `std::swap`
template <class Range, class Indices> requires(std::ranges::range<Range>)
const Indices& rearrange(Range& a, const Indices& p) {
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

template <class Range,
          class Compare = std::less<std::ranges::range_value_t<Range>>>
requires(std::ranges::range<Range>)
std::vector<int> sorted_indices(const Range& a, Compare compare = Compare()) {
  std::vector<int> p(a.size());
  std::iota(p.begin(), p.end(), 0);
  std::sort(p.begin(), p.end(), [&](int i, int j) {
    return compare(a[i], a[j]) || (!compare(a[j], a[i]) && i < j);
  });
  return p;
}

template <class Range,
          class Compare = std::less<std::ranges::range_value_t<Range>>>
requires(std::ranges::range<Range>)
std::vector<int> sort(Range& a, Compare compare = Compare()) {
  return rearrange(a, sorted_indices(a, compare));
}

template <class Range,
          class Compare = std::less<std::ranges::range_value_t<Range>>>
requires(std::ranges::range<Range>)
std::vector<int> compress(Range a, Compare compare = Compare()) {
  int n = int(a.size());
  std::vector<int> res(n);
  auto p = sort(a, compare);
  for (int i = 0, j = 0; i < n; i++) {
    if (i > 0 && compare(a[i - 1], a[i])) j++;
    res[p[i]] = j;
  }
  return res;
}

template <class Range> requires(std::ranges::range<Range>)
Range inverse(const Range& p) {
  Range q(p.size());
  std::fill(q.begin(), q.end(), -1);
  for (int i = 0; i < int(p.size()); i++) {
    assert(0 <= p[i] && p[i] < int(p.size()));
    assert(q[p[i]] == -1);
    q[p[i]] = i;
  }
  return q;
}

}  // namespace cp