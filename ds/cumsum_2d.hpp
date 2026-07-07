#pragma once

#include <cassert>
#include <vector>

namespace cp {

template <class T> struct cumsum_2d {
public:
  struct row {
  public:
    row() : row(0) {}
    explicit row(int _w) : w(_w), d(_w) {}
    explicit row(int _w, T x) : w(_w), d(_w, x) {}

    T& operator[](int j) {
      assert(0 <= j && j < w);
      return d[j];
    }
    T operator[](int j) const {
      assert(0 <= j && j < w);
      return d[j];
    }

  private:
    int w;
    std::vector<T> d;
  };

  cumsum_2d() : h(0), w(0) {}
  cumsum_2d(int _h, int _w) : h(_h), w(_w), d(_h, row(_w)) {}
  cumsum_2d(int _h, int _w, T x) : h(_h), w(_w), d(_h, row(_w, x)) {}

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

  row& operator[](int i) {
    assert(0 <= i && i < h);
    return d[i];
  }
  const row& operator[](int i) const {
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

  void imos(int hl, int wl, int hr, int wr, T x) {
    assert(0 <= hl && hl <= hr && hr <= h);
    assert(0 <= wl && wl <= wr && wr <= w);
    if (hl < h && wl < w) d[hl][wl] += x;
    if (hl < h && wr < w) d[hl][wr] -= x;
    if (hr < h && wl < w) d[hr][wl] -= x;
    if (hr < h && wr < w) d[hr][wr] += x;
  }

  int height() const { return h; }
  int width() const { return w; }

private:
  int h, w;
  bool accumulated = false;
  std::vector<row> d;
  std::vector<std::vector<T>> cum;
};

} // namespace cp