#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace cp {

// preliminary rectangle add -> rectangle sum (both offline)
template <class T, class U> class offline_rectangle_add_rectangle_sum {
 public:
  offline_rectangle_add_rectangle_sum() {}

  void add(T l, T d, T r, T u, U w) {
    assert(!asked_sum);
    assert(l <= r && d <= u);
    upper_right_add(l, d, w);
    upper_right_add(l, u, -w);
    upper_right_add(r, d, -w);
    upper_right_add(r, u, w);
  }

  void sum(T l, T d, T r, T u) {
    assert(l <= r && d <= u);
    asked_sum = true;
    lower_left_sum(l, d, qn, false);
    lower_left_sum(l, u, qn, true);
    lower_left_sum(r, d, qn, true);
    lower_left_sum(r, u, qn, false);
    qn++;
  }

  std::vector<U> run() {
    std::sort(ps.begin(), ps.end());
    std::sort(qs.begin(), qs.end());
    std::sort(ys.begin(), ys.end());
    ys.erase(std::unique(ys.begin(), ys.end()), ys.end());

    std::vector<V> fenwick(ys.size() + 1, V{0, 0, 0, 0});
    std::vector<U> res(qn);
    int i = 0;
    for (Q& q : qs) {
      while (i < int(ps.size()) && ps[i].x < q.x) {
        auto lb = std::lower_bound(ys.begin(), ys.end(), ps[i].y);
        int j = int(lb - ys.begin()) + 1;
        while (j < int(fenwick.size())) {
          fenwick[j] += ps[i].v;
          j += j & -j;
        }
        i++;
      }
      V s = {0, 0, 0, 0};
      int j = int(std::lower_bound(ys.begin(), ys.end(), q.y) - ys.begin());
      while (j > 0) {
        s += fenwick[j];
        j -= j & -j;
      }
      U v = s.a * q.x * q.y - s.b * q.x - s.c * q.y + s.d;
      res[q.id] += (q.neg ? -v : v);
    }
    return res;
  }

 private:
  struct V {
    U a, b, c, d;
    V& operator+=(const V& rhs) {
      a += rhs.a;
      b += rhs.b;
      c += rhs.c;
      d += rhs.d;
      return *this;
    }
  };
  struct P {
    T x, y;
    V v;
    friend bool operator<(const P& lhs, const P& rhs) { return lhs.x < rhs.x; }
  };
  struct Q {
    T x, y;
    int id;
    bool neg;
    friend bool operator<(const Q& lhs, const Q& rhs) { return lhs.x < rhs.x; }
  };

  std::vector<P> ps;
  std::vector<Q> qs;
  std::vector<T> ys;
  int qn = 0;
  bool asked_sum = false;

  void lower_left_sum(T r, T u, int id, bool neg) {
    qs.push_back(Q{r, u, id, neg});
  }
  void upper_right_add(T l, T d, U w) {
    V v = {w, w * U(d), w * U(l), w * U(l) * U(d)};
    ps.push_back(P{l, d, v});
    ys.push_back(d);
  }
};

}  // namespace cp