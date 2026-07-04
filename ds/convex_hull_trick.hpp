#pragma once

#include <cassert>
#include <deque>

namespace cp {

template <class T, bool is_max = false> struct convex_hull_trick {
public:
  convex_hull_trick() {}

  void add(T a, T b) {
    if (!ls.emtpy()) {
      if constexpr (is_max) assert(ls.back().a <= a);
      else assert(a <= ls.back().a);
    }
    line l(a, b);
    while (ls.size() >= 2) {
      const line& l1 = ls[ls.size() - 2];
      const line& l2 = ls.back();
      if ((l.a - l2.a) * (l1.b - l2.b) < (l2.a - l1.a) * (l2.b - l.b)) break;
      ls.pop_back();
    }
    ls.push_back(l);
  }

  T query(T x) {
    assert(!ls.empty());
    T cur = ls[0](x);
    while (int(ls.size()) >= 2) {
      T nxt = ls[1](x);
      if constexpr (is_max) {
        if (nxt < cur) break;
      } else {
        if (nxt > cur) break; 
      }
      cur = nxt;
      ls.pop_front();
    }
    return cur;
  }

private:
  struct line {
    T a, b;
    line(T _a = 0, T _b = 0) : a(_a), b(_b) {}
    T operator()(T x) const { return a * x + b; }
  };
  std::deque<line> ls;
};

} // namespace cp