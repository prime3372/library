#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace cp {

template <class T, class Compare = std::less<T>> class coordinate_compression {
 public:
  coordinate_compression() {}
  explicit coordinate_compression(const std::vector<T>& v) { build(v); }

  void build(const std::vector<T>& v) {
    d = v;
    std::sort(d.begin(), d.end(), Compare());
    d.erase(std::unique(d.begin(), d.end(),
                        [&](const T& x, const T& y) {
                          return !Compare()(x, y) && !Compare()(y, x);
                        }),
            d.end());
    initialized = true;
  }

  int operator()(const T& x) const {
    assert(initialized);
    return int(std::lower_bound(d.begin(), d.end(), x) - d.begin());
  }

  const T& operator[](int i) const {
    assert(initialized);
    assert(0 <= i && i < int(d.size()));
    return d[i];
  }

  int size() const { return int(d.size()); }

 private:
  std::vector<T> d;
  bool initialized = false;
};

}  // namespace cp