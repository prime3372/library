#pragma once

#include <cassert>
#include <iostream>
#include <vector>

#include "ds/fenwick_tree.hpp"

namespace cp {

template <class T> class fenwick_tree_2d {
 public:
  fenwick_tree_2d() : X(0), Y(0) {}
  explicit fenwick_tree_2d(int _h, int _w) : X(_h), Y(_w), d(_h) {
    for (int x = 0; x < X; x++) {
      d[x] = fenwick_tree<T>(Y);
    }
  }

  void add(int x, int y, T w) {
    assert(0 <= x && x < X);
    assert(0 <= y && y < Y);
    x++;
    while (x <= X) {
      d[x - 1].add(y, w);
      x += x & -x;
    }
  }

  class ref {
   public:
    T operator[](int y) const {
      assert(0 <= y && y < ptr->Y);
      return ptr->sum(x, y, x + 1, y + 1);
    }
    ref(const fenwick_tree_2d* _ptr, int _i) : ptr(_ptr), x(_i) {}

   private:
    const fenwick_tree_2d* ptr;
    int x;
  };

  ref operator[](int x) const {
    assert(0 <= x && x < X);
    return ref(this, x);
  }

  T sum(int xl, int yl, int xr, int yr) const {
    assert(0 <= xl && xl <= xr && xr <= X);
    assert(0 <= yl && yl <= yr && yr <= Y);
    return sum(xr, yr) - sum(xr, yl) - sum(xl, yr) + sum(xl, yl);
  }

  T sum(int x, int y) const {
    assert(0 <= x && x <= X);
    assert(0 <= y && y <= Y);
    T res = 0;
    while (x) {
      res += d[x - 1].sum(y);
      x -= x & -x;
    }
    return res;
  }

  void imos_add(int xl, int yl, int xr, int yr, T w) {
    assert(0 <= xl && xl <= xr && xr <= X);
    assert(0 <= yl && yl <= yr && yr <= Y);
    if (xl < X && yl < Y) add(xl, yl, w);
    if (xl < X && yr < Y) add(xl, yr, -w);
    if (xr < X && yl < Y) add(xr, yl, -w);
    if (xr < X && yr < Y) add(xr, yr, w);
  }

  T imos_get(int x, int y) const {
    assert(0 <= x && x < X);
    assert(0 <= y && y < Y);
    return sum(x + 1, y + 1);
  }

  friend std::ostream& operator<<(std::ostream& os, const fenwick_tree_2d& fw) {
    for (int x = 0; x < fw.X; x++) {
      for (int y = 0; y < fw.Y; y++) {
        os << fw[x][y];
        if (y != fw.Y - 1) os << " ";
      }
      if (x != fw.X - 1) os << "\n";
    }
    return os;
  }

 private:
  int X, Y;
  std::vector<fenwick_tree<T>> d;
};

}  // namespace cp