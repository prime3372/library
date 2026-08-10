#pragma once

#include <cassert>
#include <iostream>
#include <vector>

#include "util/io_utility.hpp"

namespace cp {

template <class T> struct cumsum_2d {
public:
  cumsum_2d() : h(0), w(0) {}
  cumsum_2d(int _h, int _w) : h(_h), w(_w), d(_h, std::vector<T>(_w)) {}
  cumsum_2d(int _h, int _w, T x) : h(_h), w(_w), d(_h, std::vector<T>(_w, x)) {}

  void accumulate() {
    cum.resize(h + 1, std::vector<T>(w + 1));
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        cum[i + 1][j + 1] = cum[i + 1][j] + d[i][j];
      }
    }
    for (int j = 0; j < w; j++) {
      for (int i = 0; i < h; i++) {
        cum[i + 1][j + 1] += cum[i][j + 1];
      }
    }
    accumulated = true;
  }

  std::vector<T>& operator[](int i) {
    assert(0 <= i && i < h);
    return d[i];
  }
  const std::vector<T>& operator[](int i) const {
    assert(0 <= i && i < h);
    return d[i];
  }

  T sum(int hr, int wr) {
    assert(0 <= hr && hr <= h);
    assert(0 <= wr && wr <= w);
    if (!accumulated) accumulate();
    return cum[hr][wr];
  }

  T sum(int hl, int wl, int hr, int wr) {
    assert(0 <= hl && hl <= hr && hr <= h);
    assert(0 <= wl && wl <= wr && wr <= w);
    if (!accumulated) accumulate();
    return cum[hr][wr] - cum[hr][wl] - cum[hl][wr] + cum[hl][wl];
  }

  void imos_add(int hl, int wl, int hr, int wr, T x) {
    assert(0 <= hl && hl <= hr && hr <= h);
    assert(0 <= wl && wl <= wr && wr <= w);
    if (hl < h && wl < w) d[hl][wl] += x;
    if (hl < h && wr < w) d[hl][wr] -= x;
    if (hr < h && wl < w) d[hr][wl] -= x;
    if (hr < h && wr < w) d[hr][wr] += x;
  }

  T imos_get(int i, int j) {
    assert(0 <= i && i < h);
    assert(0 <= j && j < w);
    return sum(i + 1, j + 1);
  }

  int height() const { return h; }
  int width() const { return w; }

  // for debugging
  friend std::ostream& operator<<(std::ostream& os, const cumsum_2d& sum) {
    for (int i = 0; i < sum.h; i++) {
      for (int j = 0; j < sum.w; j++) {
        os << sum[i][j];
        if (j != sum.w - 1) os << " ";
      }
      if (i != sum.h - 1) os << "\n";
    }
    return os;
  }

private:
  int h, w;
  bool accumulated = false;
  std::vector<std::vector<T>> d;
  std::vector<std::vector<T>> cum;
};

} // namespace cp