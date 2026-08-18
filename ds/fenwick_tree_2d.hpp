#pragma once

#include <cassert>
#include <iostream>
#include <vector>

#include "ds/fenwick_tree.hpp"

namespace cp {

template <class T> class fenwick_tree_2d {
 public:
  fenwick_tree_2d() : xmax(0), ymax(0) {}
  fenwick_tree_2d(int _h, int _w) : xmax(_h), ymax(_w), d(_h) {
    for (int x = 0; x < xmax; x++) {
      d[x] = fenwick_tree<T>(ymax);
    }
  }

  void add(int x, int y, T w) {
    assert(0 <= x && x < xmax);
    assert(0 <= y && y < ymax);
    x++;
    while (x <= xmax) {
      d[x - 1].add(y, w);
      x += x & -x;
    }
  }

  class ref {
   public:
    T operator[](int y) const {
      assert(0 <= y && y < ptr->ymax);
      return ptr->sum(x, y, x + 1, y + 1);
    }
    ref(const fenwick_tree_2d* _ptr, int _i) : ptr(_ptr), x(_i) {}

   private:
    const fenwick_tree_2d* ptr;
    int x;
  };

  ref operator[](int x) const {
    assert(0 <= x && x < xmax);
    return ref(this, x);
  }

  T sum(int x, int y) const {
    assert(0 <= x && x <= xmax);
    assert(0 <= y && y <= ymax);
    T res = 0;
    while (x) {
      res += d[x - 1].sum(y);
      x -= x & -x;
    }
    return res;
  }

  T sum(int xl, int yl, int xr, int yr) const {
    assert(0 <= xl && xl <= xr && xr <= xmax);
    assert(0 <= yl && yl <= yr && yr <= ymax);
    return sum(xr, yr) - sum(xr, yl) - sum(xl, yr) + sum(xl, yl);
  }

  void imos_add(int xl, int yl, int xr, int yr, T w) {
    assert(0 <= xl && xl <= xr && xr <= xmax);
    assert(0 <= yl && yl <= yr && yr <= ymax);
    if (xl < xmax && yl < ymax) add(xl, yl, w);
    if (xl < xmax && yr < ymax) add(xl, yr, -w);
    if (xr < xmax && yl < ymax) add(xr, yl, -w);
    if (xr < xmax && yr < ymax) add(xr, yr, w);
  }

  T imos_get(int x, int y) const {
    assert(0 <= x && x < xmax);
    assert(0 <= y && y < ymax);
    return sum(x + 1, y + 1);
  }

  friend std::ostream& operator<<(std::ostream& os, const fenwick_tree_2d& fw) {
    for (int x = 0; x < fw.xmax; x++) {
      for (int y = 0; y < fw.ymax; y++) {
        os << fw[x][y];
        if (y != fw.ymax - 1) os << " ";
      }
      if (x != fw.xmax - 1) os << "\n";
    }
    return os;
  }

 private:
  int xmax, ymax;
  std::vector<fenwick_tree<T>> d;
};

}  // namespace cp