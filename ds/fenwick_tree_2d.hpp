#pragma once

#include <cassert>
#include <iostream>
#include <vector>

#include "ds/fenwick_tree.hpp"
#include "util/io_utility.hpp"

namespace cp {

template <class T> struct fenwick_tree_2d {
public:
  fenwick_tree_2d() : h(0), w(0) {}
  fenwick_tree_2d(int _h, int _w) : h(_h), w(_w), d(_h) {
    for (int i = 0; i < h; i++) {
      d[i] = fenwick_tree<T>(w);
    }
  }

  void add(int i, int j, T x) {
    assert(0 <= i && i < h);
    assert(0 <= j && j < w);
    i++;
    while (i <= h) {
      d[i - 1].add(j, x);
      i += i & -i;
    }
  }

  struct ref {
  public:
    T operator[](int j) const {
      assert(0 <= j && j < ptr->w);
      return ptr->sum(i, j, i + 1, j + 1);
    }
    ref(const fenwick_tree_2d* _ptr, int _i) : ptr(_ptr), i(_i) {}
  private:
    const fenwick_tree_2d* ptr;
    int i;
  };

  ref operator[](int i) const {
    assert(0 <= i && i < h);
    return ref(this, i);
  }

  T sum(int i, int j) const {
    assert(0 <= i && i <= h);
    assert(0 <= j && j <= w);
    T res = 0;
    while (i) {
      res += d[i - 1].sum(j);
      i -= i & -i;
    }
    return res;
  }

  T sum(int hl, int wl, int hr, int wr) const {
    assert(0 <= hl && hl <= hr && hr <= h);
    assert(0 <= wl && wl <= wr && wr <= w);
    return sum(hr, wr) - sum(hr, wl) - sum(hl, wr) + sum(hl, wl);
  }

  void imos_add(int hl, int wl, int hr, int wr, T x) {
    assert(0 <= hl && hl <= hr && hr <= h);
    assert(0 <= wl && wl <= wr && wr <= w);
    if (hl < h && wl < w) add(hl, wl, x);
    if (hl < h && wr < w) add(hl, wr, -x);
    if (hr < h && wl < w) add(hr, wl, -x);
    if (hr < h && wr < w) add(hr, wr, x);
  }

  T imos_get(int i, int j) const {
    assert(0 <= i && i < h);
    assert(0 <= j && j < w);
    return sum(i + 1, j + 1);
  }

  int height() const { return h; }
  int width() const { return w; }

  // for debugging
  friend std::ostream& operator<<(std::ostream& os, const fenwick_tree_2d& fw) {
    for (int i = 0; i < fw.h; i++) {
      for (int j = 0; j < fw.w; j++) {
        os << fw[i][j];
        if (j != fw.w - 1) os << " ";
      }
      if (i != fw.h - 1) os << "\n";
    }
    return os;
  }

private:
  int h, w;
  std::vector<fenwick_tree<T>> d;
};

namespace internal {

template <class T> struct delimiter<fenwick_tree_2d<T>> {
  static constexpr char value = '\n';
};

} // namespace internal


} // namespace cp