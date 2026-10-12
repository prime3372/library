#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <vector>

namespace cp {

template <bool strong = true, class T, class Compare = std::less<T>>
int length_of_lis(const std::vector<T>& a, Compare compare = Compare()) {
  int n = int(a.size());
  std::vector<T> dp(n, std::numeric_limits<T>::max());
  int ans = 0;
  for (int i = 0; i < n; i++) {
    auto itr = strong ? std::lower_bound(dp.begin(), dp.end(), a[i], compare)
                      : std::upper_bound(dp.begin(), dp.end(), a[i], compare);
    int k = int(itr - dp.begin());
    assert(k < n);
    dp[k] = a[i];
    ans = std::max(ans, k + 1);
  }
  return ans;
}

}  // namespace cp