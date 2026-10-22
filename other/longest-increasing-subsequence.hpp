#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <vector>

namespace cp {

template <class T, class Compare = std::less<T>>
std::pair<int, std::vector<int>> longest_increasing_subsequence(
    const std::vector<T>& a,
    Compare compare = Compare{}) {
  int n = int(a.size());
  int ans = 0;
  std::vector<T> dp(n, std::numeric_limits<T>::max());
  for (int i = 0; i < n; i++) {
    auto itr = std::lower_bound(dp.begin(), dp.end(), a[i], compare);
    int k = int(itr - dp.begin());
    // assert(k < n);
    dp[k] = a[i];
    ans = std::max(ans, k + 1);
  }
  return ans;
}

template <class T, class Compare = std::less<T>>
std::pair<int, std::vector<int>> longest_nondecreasing_subsequence(
    const std::vector<T>& a,
    Compare compare = Compare{}) {
  // awdgen
}

}  // namespace cp