#pragma once

#include <cassert>
#include <iostream>
#include <vector>

#include "util/io_utility.hpp"

namespace cp {

template <class T> class cumsum_2d {
 public:
  cumsum_2d() : X(0), Y(0) {}
  explicit cumsum_2d(int x, int y) : X(x), Y(y), val(x, std::vector<T>(y)) {}
  explicit cumsum_2d(int x, int y, const T& w)
      : X(x), Y(y), val(x, std::vector<T>(y, w)) {}

  void accumulate() {
    cum.resize(X + 1, std::vector<T>(Y + 1));
    for (int x = 0; x < X; x++) {
      for (int y = 0; y < Y; y++) {
        cum[x + 1][y + 1] = cum[x + 1][y] + val[x][y];
      }
    }
    for (int y = 0; y < Y; y++) {
      for (int x = 0; x < X; x++) {
        cum[x + 1][y + 1] += cum[x][y + 1];
      }
    }
    accumulated = true;
  }

  std::vector<T>& operator[](int x) {
    assert(0 <= x && x < X);
    return val[x];
  }
  const std::vector<T>& operator[](int x) const {
    assert(0 <= x && x < X);
    return val[x];
  }

  T sum(int xr, int yr) {
    assert(0 <= xr && xr <= X);
    assert(0 <= yr && yr <= Y);
    if (!accumulated) accumulate();
    return cum[xr][yr];
  }

  T sum(int xl, int yl, int xr, int yr) {
    assert(0 <= xl && xl <= xr && xr <= X);
    assert(0 <= yl && yl <= yr && yr <= Y);
    if (!accumulated) accumulate();
    return cum[xr][yr] - cum[xr][yl] - cum[xl][yr] + cum[xl][yl];
  }

  void imos_add(int xl, int yl, int xr, int yr, T w) {
    assert(0 <= xl && xl <= xr && xr <= X);
    assert(0 <= yl && yl <= yr && yr <= Y);
    if (xl < X && yl < Y) val[xl][yl] += w;
    if (xl < X && yr < Y) val[xl][yr] -= w;
    if (xr < X && yl < Y) val[xr][yl] -= w;
    if (xr < X && yr < Y) val[xr][yr] += w;
  }

  T imos_get(int x, int y) {
    assert(0 <= x && x < X);
    assert(0 <= y && y < Y);
    return sum(x + 1, y + 1);
  }

  friend std::ostream& operator<<(std::ostream& os, const cumsum_2d& sum) {
    for (int x = 0; x < sum.X; x++) {
      for (int y = 0; y < sum.Y; y++) {
        os << sum[x][y];
        if (y != sum.Y - 1) os << " ";
      }
      if (x != sum.X - 1) os << "\n";
    }
    return os;
  }

 private:
  int X, Y;
  bool accumulated = false;
  std::vector<std::vector<T>> val;
  std::vector<std::vector<T>> cum;
};

}  // namespace cp