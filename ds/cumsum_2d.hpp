#pragma once

#include <cassert>
#include <iostream>
#include <vector>

#include "util/io_utility.hpp"

namespace cp {

template <class T> class cumsum_2d {
 public:
  cumsum_2d() : xmax(0), ymax(0) {}
  explicit cumsum_2d(int x, int y)
      : xmax(x), ymax(y), val(x, std::vector<T>(y)) {}
  explicit cumsum_2d(int x, int y, const T& w)
      : xmax(x), ymax(y), val(x, std::vector<T>(y, w)) {}

  void accumulate() {
    cum.resize(xmax + 1, std::vector<T>(ymax + 1));
    for (int x = 0; x < xmax; x++) {
      for (int y = 0; y < ymax; y++) {
        cum[x + 1][y + 1] = cum[x + 1][y] + val[x][y];
      }
    }
    for (int y = 0; y < ymax; y++) {
      for (int x = 0; x < xmax; x++) {
        cum[x + 1][y + 1] += cum[x][y + 1];
      }
    }
    accumulated = true;
  }

  std::vector<T>& operator[](int x) {
    assert(0 <= x && x < xmax);
    return val[x];
  }
  const std::vector<T>& operator[](int x) const {
    assert(0 <= x && x < xmax);
    return val[x];
  }

  T sum(int xr, int yr) {
    assert(0 <= xr && xr <= xmax);
    assert(0 <= yr && yr <= ymax);
    if (!accumulated) accumulate();
    return cum[xr][yr];
  }

  T sum(int xl, int yl, int xr, int yr) {
    assert(0 <= xl && xl <= xr && xr <= xmax);
    assert(0 <= yl && yl <= yr && yr <= ymax);
    if (!accumulated) accumulate();
    return cum[xr][yr] - cum[xr][yl] - cum[xl][yr] + cum[xl][yl];
  }

  void imos_add(int xl, int yl, int xr, int yr, T w) {
    assert(0 <= xl && xl <= xr && xr <= xmax);
    assert(0 <= yl && yl <= yr && yr <= ymax);
    if (xl < xmax && yl < ymax) val[xl][yl] += w;
    if (xl < xmax && yr < ymax) val[xl][yr] -= w;
    if (xr < xmax && yl < ymax) val[xr][yl] -= w;
    if (xr < xmax && yr < ymax) val[xr][yr] += w;
  }

  T imos_get(int x, int y) {
    assert(0 <= x && x < xmax);
    assert(0 <= y && y < ymax);
    return sum(x + 1, y + 1);
  }

  friend std::ostream& operator<<(std::ostream& os, const cumsum_2d& sum) {
    for (int x = 0; x < sum.xmax; x++) {
      for (int y = 0; y < sum.ymax; y++) {
        os << sum[x][y];
        if (y != sum.ymax - 1) os << " ";
      }
      if (x != sum.xmax - 1) os << "\n";
    }
    return os;
  }

 private:
  int xmax, ymax;
  bool accumulated = false;
  std::vector<std::vector<T>> val;
  std::vector<std::vector<T>> cum;
};

}  // namespace cp