#pragma once

#include <algorithm>
#include <limits>
#include <vector>

namespace cp {

template <bool strong = true, class T>
int length_of_lis(const std::vector<T>& a) {
  int n = int(a.size());
  std::vector<T> dp(n, std::numeric_limits<T>::max());
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int j;
    if (strong) {
      j = int(std::lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin());
    } else {
      j = int(std::upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin());
    }
    dp[j] = a[i];
    ans = std::max(ans, j + 1);
  }
  return ans;
}

} // namespace cp