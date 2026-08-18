#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

#include "ds/dynamic_fenwick_tree.hpp"

namespace cp {

template <class T> class dynamic_fenwick_tree_2d {
 public:
  dynamic_fenwick_tree_2d() : xmax(0), ymax(0) {}
  dynamic_fenwick_tree_2d(int _h, size_t _w) : xmax(_h), ymax(_w), d(_h) {
    for (int x = 0; x < xmax; x++) d[x] = dynamic_fenwick_tree<T>(ymax);
  }

  void add(int x, size_t y, T w) {
    assert(0 <= x && x < xmax);
    assert(y < ymax);
    x++;
    while (x <= xmax) {
      d[x - 1].add(y, w);
      x += x & -x;
    }
  }

  class ref {
   public:
    T operator[](size_t y) const {
      assert(y < ptr->ymax);
      return ptr->sum(x, y, x + 1, y + 1);
    }
    ref(const dynamic_fenwick_tree_2d* _ptr, int _i) : ptr(_ptr), x(_i) {}

   private:
    const dynamic_fenwick_tree_2d* ptr;
    int x;
  };

  ref operator[](int x) const {
    assert(x < xmax);
    return ref(this, x);
  }

  T sum(int x, size_t y) const {
    assert(0 <= x && x <= xmax);
    assert(y <= ymax);
    T s = 0;
    while (x) {
      s += d[x - 1].sum(y);
      x -= x & -x;
    }
    return s;
  }

  T sum(int xl, size_t yl, int xr, size_t yr) const {
    assert(0 <= xl && xl <= xr && xr <= xmax);
    assert(yl <= yr && yr <= ymax);
    return sum(xr, yr) - sum(xr, yl) - sum(xl, yr) + sum(xl, yl);
  }

  void imos_add(int xl, size_t yl, int xr, size_t yr, T w) {
    assert(0 <= xl && xl <= xr && xr <= xmax);
    assert(yl <= yr && yr <= ymax);
    if (xl < xmax && yl < ymax) add(xl, yl, w);
    if (xl < xmax && yr < ymax) add(xl, yr, -w);
    if (xr < xmax && yl < ymax) add(xr, yl, -w);
    if (xr < xmax && yr < ymax) add(xr, yr, w);
  }

  T imos_get(int x, size_t y) const {
    assert(0 <= x && x < xmax);
    assert(y < ymax);
    return sum(x + 1, y + 1);
  }

  friend std::ostream& operator<<(std::ostream& os,
                                  const dynamic_fenwick_tree_2d& fw) {
    for (int x = 0; x < fw.xmax; x++) {
      for (size_t y = 0; y < fw.ymax; y++) {
        os << fw[x][y];
        if (y != fw.ymax - 1) os << " ";
      }
      if (x != fw.xmax - 1) os << "\n";
    }
    return os;
  }

 private:
  int xmax;
  size_t ymax;
  std::vector<dynamic_fenwick_tree<T>> d;
};

}  // namespace cp