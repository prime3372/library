#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

namespace cp {

// even index -> min heap, odd index -> max heap
template <class T> struct double_ended_priority_queue {

  double_ended_priority_queue() : d(2) {}

  T min() const {
    assert(!empty());
    return d[2];
  }
  T max() const {
    assert(!empty());
    return int(d.size()) == 3 ? d[2] : d[3];
  }

  void push(T x) {
    d.push_back(x);
    up(int(d.size()) - 1);
  }

  void pop_min() {
    assert(!empty());
    if (int(d.size()) == 3) {
      d.pop_back();
      return;
    }
    std::swap(d[2], d.back());
    d.pop_back();
    up(down(2));
  }
  void pop_max() {
    assert(!empty());
    if (int(d.size()) <= 4) {
      d.pop_back(); 
      return;
    }
    std::swap(d[3], d.back());
    d.pop_back();
    up(down(3));
  }

  int size() const { return int(d.size()) - 2; }
  bool empty() const { return size() == 0; }

private:
  std::vector<T> d;

  int down(int cur) {
    int n = int(d.size());
    if (cur == 2) {
      while (true) {
        int nxt = 2 * cur;
        if (nxt + 2 < n && d[nxt] > d[nxt + 2]) nxt += 2;
        if (nxt < n && d[cur] > d[nxt]) {
          std::swap(d[cur], d[nxt]);
          cur = nxt;
        } else break;
      }
    } else {
      while (true) {
        int nxt = 2 * (cur - 1) + 1;
        if (nxt + 2 < n && d[nxt] < d[nxt + 2]) nxt += 2;
        if (nxt < n && d[cur] < d[nxt]) {
          std::swap(d[cur], d[nxt]);
          cur = nxt;
        } else break;
      }
    }
    return cur;
  }

  int up(int cur) {
    int n = int(d.size());
    if ((cur | 1) < n && d[cur & ~1] > d[cur | 1]) {
      std::swap(d[cur & ~1], d[cur | 1]);
      cur ^= 1;
    }
    if (d[cur] < d[cur / 4 * 2]) {
      while (true) {
        int nxt = cur / 4 * 2;
        if (cur >= 4 && d[cur] < d[nxt]) {
        std::swap(d[cur], d[nxt]);
        cur = nxt;
        } else break;
      }
    } else {
      while (true) {
        int nxt = cur / 4 * 2 + 1;
        if (cur >= 4 && d[cur] > d[nxt]) {
          std::swap(d[cur], d[nxt]);
          cur = nxt;
        } else break;
      }

    }
    return cur;
  }
};

} // namespace cp