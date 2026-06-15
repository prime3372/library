#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

template <class T> struct coordinate_compression {
public:
  coordinate_compression() {}
  coordinate_compression(const std::vector<T>& xs) {
    for (T x : xs) add(x);
  }

  void add(T x) { d.push_back(x); }

  void init() {
    std::sort(d.begin(), d.end());
    d.erase(std::unique(d.begin(), d.end()), d.end());
    initialized = true;
  }

  int operator()(const T& x) {
    if (!initialized) init();
    return int(std::lower_bound(d.begin(), d.end(), x) - d.begin());
  }

  std::vector<int> operator()(const std::vector<T>& xs) {
    if (!initialized) init();
    std::vector<int> res(xs.size());
    for (int i = 0; i < int(xs.size()); i++) {
      res[i] = (*this)(xs[i]);
    }
    return res;
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

private:
  bool initialized = false;
  std::vector<T> d;
};
