#pragma once

#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

#include "ds/dynamic_fenwick_tree.hpp"

namespace cp {

template <class T> struct dynamic_fenwick_tree_2d {
public: 
  struct ref {
  public:
    T operator[](size_t j) const {
      assert(j < ptr->w);
      return ptr->sum(i, j, i + 1, j + 1);
    }
    ref(const dynamic_fenwick_tree_2d<T>* _ptr, int _i) : ptr(_ptr), i(_i) {}
  private:
    const dynamic_fenwick_tree_2d<T>* ptr;
    int i;
  };

  dynamic_fenwick_tree_2d() : h(0), w(0) {}
  dynamic_fenwick_tree_2d(int _h, size_t _w) : h(_h), w(_w), d(_h) {
    for (int i = 0; i < h; i++) {
      d[i] = dynamic_fenwick_tree<T>(w);
    }
  }

  void add(int i, size_t j, T x) {
    assert(0 <= i && i < h);
    assert(j < w);
    i++;
    while (i <= h) {
      d[i - 1].add(j, x);
      i += i & -i;
    }
  }

  ref operator[](int i) const {
    assert(i < h);
    return ref(this, i);
  }

  T sum(int i, size_t j) const {
    assert(0 <= i && i <= h);
    assert(j <= w);
    T s = 0;
    while (i) {
      s += d[i - 1].sum(j);
      i -= i & -i;
    }
    return s;
  }

  T sum(int hl, size_t wl, int hr, size_t wr) const {
    assert(0 <= hl && hl <= hr && hr <= h);
    assert(wl <= wr && wr <= w);
    return sum(hr, wr) - sum(hr, wl) - sum(hl, wr) + sum(hl, wl);
  }

  void imos_add(int hl, size_t wl, int hr, size_t wr, T x) {
    assert(0 <= hl && hl <= hr && hr <= h);
    assert(wl <= wr && wr <= w);
    if (hl < h && wl < w) add(hl, wl, x);
    if (hl < h && wr < w) add(hl, wr, -x);
    if (hr < h && wl < w) add(hr, wl, -x);
    if (hr < h && wr < w) add(hr, wr, x);
  }

  T imos_get(int i, size_t j) const {
    assert(0 <= i && i < h);
    assert(j < w);
    return sum(i + 1, j + 1);
  }

  int height() const { return h; }
  size_t width() const { return w; }

  // for debugging
  friend std::ostream& operator<<(std::ostream& os, const dynamic_fenwick_tree_2d& fw) {
    for (int i = 0; i < fw.h; i++) {
      for (size_t j = 0; j < fw.w; j++) {
        os << fw[i][j];
        if (j != fw.w - 1) os << " ";
      }
      if (i != fw.h - 1) os << "\n";
    }
    return os;
  }

private:
  int h;
  size_t w;
  std::vector<dynamic_fenwick_tree<T>> d;
};

} // namespace cp