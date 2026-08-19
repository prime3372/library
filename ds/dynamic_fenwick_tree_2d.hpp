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
  dynamic_fenwick_tree_2d() : X(0), Y(0) {}
  dynamic_fenwick_tree_2d(int _h, size_t _w) : X(_h), Y(_w), d(_h) {
    for (int x = 0; x < X; x++) d[x] = dynamic_fenwick_tree<T>(Y);
  }

  void add(int x, size_t y, T w) {
    assert(0 <= x && x < X);
    assert(y < Y);
    x++;
    while (x <= X) {
      d[x - 1].add(y, w);
      x += x & -x;
    }
  }

  class ref {
   public:
    T operator[](size_t y) const {
      assert(y < ptr->Y);
      return ptr->sum(x, y, x + 1, y + 1);
    }
    ref(const dynamic_fenwick_tree_2d* _ptr, int _i) : ptr(_ptr), x(_i) {}

   private:
    const dynamic_fenwick_tree_2d* ptr;
    int x;
  };

  ref operator[](int x) const {
    assert(x < X);
    return ref(this, x);
  }

  T sum(int x, size_t y) const {
    assert(0 <= x && x <= X);
    assert(y <= Y);
    T s = 0;
    while (x) {
      s += d[x - 1].sum(y);
      x -= x & -x;
    }
    return s;
  }

  T sum(int xl, size_t yl, int xr, size_t yr) const {
    assert(0 <= xl && xl <= xr && xr <= X);
    assert(yl <= yr && yr <= Y);
    return sum(xr, yr) - sum(xr, yl) - sum(xl, yr) + sum(xl, yl);
  }

  void imos_add(int xl, size_t yl, int xr, size_t yr, T w) {
    assert(0 <= xl && xl <= xr && xr <= X);
    assert(yl <= yr && yr <= Y);
    if (xl < X && yl < Y) add(xl, yl, w);
    if (xl < X && yr < Y) add(xl, yr, -w);
    if (xr < X && yl < Y) add(xr, yl, -w);
    if (xr < X && yr < Y) add(xr, yr, w);
  }

  T imos_get(int x, size_t y) const {
    assert(0 <= x && x < X);
    assert(y < Y);
    return sum(x + 1, y + 1);
  }

  friend std::ostream& operator<<(std::ostream& os,
                                  const dynamic_fenwick_tree_2d& fw) {
    for (int x = 0; x < fw.X; x++) {
      for (size_t y = 0; y < fw.Y; y++) {
        os << fw[x][y];
        if (y != fw.Y - 1) os << " ";
      }
      if (x != fw.X - 1) os << "\n";
    }
    return os;
  }

 private:
  int X;
  size_t Y;
  std::vector<dynamic_fenwick_tree<T>> d;
};

}  // namespace cp