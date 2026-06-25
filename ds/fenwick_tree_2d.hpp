#pragma once

#include <cassert>
#include <vector>
#include "fenwick_tree.hpp"

template <class T> struct fenwick_tree_2d {
public:
  struct ref {
    friend struct fenwick_tree_2d;
  public:
    T operator[](int j) const {
      assert(0 <= j && j < ptr->w);
      return ptr->sum(i, j, i + 1, j + 1);
    }
  private:
    const fenwick_tree_2d<T>* ptr;
    int i;
    ref(const fenwick_tree_2d<T>* _ptr, int _i) : ptr(_ptr), i(_i) {}
  };

  fenwick_tree_2d() : fenwick_tree_2d(0, 0) {}
  fenwick_tree_2d(int _h, int _w) : h(_h), w(_w), fw(_h) {
    for (int i = 0; i < h; i++) {
      fw[i] = fenwick_tree<T>(w);
    }
  }

  void add(int i, int j, T x) {
    assert(0 <= i && i < h);
    assert(0 <= j && j < w);
    i++;
    while (i <= h) {
      fw[i - 1].add(j, x);
      i += i & -i;
    }
  }

  ref operator[](int i) const {
    assert(0 <= i && i < h);
    return ref(this, i);
  }

  T sum(int i, int j) const {
    assert(0 <= i && i <= h);
    assert(0 <= j && j <= w);
    T res = 0;
    while (i) {
      res += fw[i - 1].sum(j);
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

private:
  int h, w;
  std::vector<fenwick_tree<T>> fw;
};
