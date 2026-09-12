#pragma once

#include <queue>
#include <utility>
#include <vector>

#include "poly/formal_power_series.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> prod(std::vector<formal_power_series<mint>> f) {
  if (f.empty()) return {1};
  std::priority_queue<std::pair<int, int>> que;
  for (int i = 0; i < int(f.size()); i++) {
    que.emplace(-f[i].size(), i);
  }
  while (que.size() > 1) {
    int i = que.top().second;
    que.pop();
    int j = que.top().second;
    que.pop();
    f[i] *= f[j];
    que.emplace(-f[i].size(), i);
  }
  return f[que.top().second];
}

}  // namespace cp