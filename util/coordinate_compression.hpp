#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "util/io_utility_base.hpp"

namespace cp {

template <class T> class coordinate_compression {
 public:
  coordinate_compression() {}
  explicit coordinate_compression(const std::vector<T>& xs) {
    for (const T& x : xs) add(x);
  }

  void add(const T& x) { d.push_back(x); }

  void init() {
    std::sort(d.begin(), d.end());
    d.erase(std::unique(d.begin(), d.end()), d.end());
    initialized = true;
  }

  int operator()(const T& x) {
    if (!initialized) init();
    return int(std::lower_bound(d.begin(), d.end(), x) - d.begin());
  }

  T operator[](int i) {
    if (!initialized) init();
    assert(0 <= i && i < int(d.size()));
    return d[i];
  }

  int size() {
    if (!initialized) init();
    return int(d.size());
  }

  friend std::ostream& operator<<(std::ostream& os, coordinate_compression cc) {
    std::vector<std::string> outs(cc.size());
    std::ostringstream oss;
    for (int i = 0; i < int(outs.size()); i++) {
      oss << cc[i];
      outs[i] = oss.str();
      oss.str("");
    }
    return os << internal::combine_outputs(outs);
  }

 private:
  bool initialized = false;
  std::vector<T> d;
};

}  // namespace cp