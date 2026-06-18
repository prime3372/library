#pragma once

#include <cassert>
#include <cstddef>
#include <vector>
#include "dynamic_fenwick_tree.hpp"

template <class T> struct dynamic_fenwick_tree_2d {
public: 
  struct ref {
    friend struct dynamic_fenwick_tree_2d;
  public:
    T operator[](size_t j) const {
      assert(j < ptr->w);
      return ptr->sum(i, j, i + 1, j + 1);
    }
  private:
    const dynamic_fenwick_tree_2d<T>* ptr;
    int i;
    ref(const dynamic_fenwick_tree_2d<T>* _ptr, int _i) : ptr(_ptr), i(_i) {}
  };

  dynamic_fenwick_tree_2d() : h(0), w(0) {}
  dynamic_fenwick_tree_2d(int _h, size_t _w) : h(_h), w(_w), fw(_h) {
    for (int i = 0; i < h; i++) {
      fw[i] = dynamic_fenwick_tree<T>(w);
    }
  }

  void add(int i, size_t j, T x) {
    assert(0 <= i && i < h);
    assert(j < w);
    i++;
    while (i <= h) {
      fw[i - 1].add(j, x);
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
      s += fw[i - 1].sum(j);
      i -= i & -i;
    }
    return s;
  }

  T sum(int hl, size_t wl, int hr, size_t wr) const {
    assert(0 <= hl && hl <= hr && hr <= h);
    assert(wl <= wr && wr <= w);
    return sum(hr, wr) - sum(hr, wl) - sum(hl, wr) + sum(hl, wl);
  }

private:
  int h;
  size_t w;
  std::vector<dynamic_fenwick_tree<T>> fw;
};
