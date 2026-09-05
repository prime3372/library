#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

  T operator[](int i) const {
    assert(initialized);
    assert(0 <= i && i < int(d.size()));
    return d[i];
  }

  int size() const { return int(d.size()); }

 private:
  bool initialized = false;
  std::vector<T> d;
};

}  // namespace cp