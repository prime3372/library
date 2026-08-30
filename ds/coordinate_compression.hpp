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
  template <class Comp = std::less<T>>
  explicit coordinate_compression(const std::vector<T>& v, Comp comp = Comp()) {
    for (const T& x : v) add(x);
    init(comp);
  }

  void add(const T& x) { d.push_back(x); }

  template <class Comp = std::less<T>> void init(Comp comp = Comp()) {
    std::sort(d.begin(), d.end(), comp);
    d.erase(std::unique(d.begin(), d.end(),
                        [&](const T& x, const T& y) {
                          return !comp(x, y) && !comp(y, x);
                        }),
            d.end());
    initialized = true;
  }

  int operator()(const T& x) const {
    assert(initialized);
    return int(std::lower_bound(d.begin(), d.end(), x) - d.begin());
  }

  std::vector<int> operator()(const std::vector<T>& v) const {
    assert(initialized);
    std::vector<int> res(v.size());
    for (int i = 0; i < int(v.size()); i++) {
      res[i] = (*this)(v[i]);
    }
    return res;
  }

  T operator[](int i) const {
    assert(initialized);
    assert(0 <= i && i < int(d.size()));
    return d[i];
  }

  int size() const { return int(d.size()); }

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