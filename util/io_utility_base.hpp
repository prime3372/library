#pragma once

#include <charconv>
#include <string>
#include <vector>

namespace cp {

namespace internal {

std::string combine_outputs(const std::vector<std::string>& outs) {
  char delimiter = ' ';
  for (const auto& s : outs) {
    double dummy;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), dummy);
    if (ec != std::errc{} || ptr != s.data() + s.size()) {
      delimiter = '\n';
    }
  }

  std::string res;
  bool first = true;
  for (const auto& s : outs) {
    if (!first) res.push_back(delimiter);
    res += s;
    first = false;
  }
  return res;
}

}  // namespace internal

}  // namespace cp