#pragma once

#include <utility>
#include <vector>

template <class T>
std::vector<std::pair<T, int>> run_length_encoding(const std::vector<T>& v) {
  if (v.empty()) return {};
  std::vector<std::pair<T, int>> res;
  res.reserve(v.size());
  for (const auto& x : v) {
    if (res.empty() || res.back().first != x) {
      res.emplace_back(x, 1);
    } else {
      res.back().second++;
    }
  }
  return res;
}