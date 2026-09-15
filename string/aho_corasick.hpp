#pragma once

#include <array>
#include <cassert>
#include <string>
#include <vector>

#include "ds/simple_queue.hpp"

namespace cp {

template <int char_size, char offset = 'a'> class aho_corasick {
 public:
  aho_corasick() : next(1), par(1, -1) { next[0].fill(-1); }

  int add(const std::string& s) {
    int v = 0;
    for (char c : s) {
      int i = c - offset;
      assert(0 <= i && i < char_size);
      if (next[v][i] == -1) {
        next[v][i] = size();
        next.emplace_back();
        next.back().fill(-1);
        par.push_back(v);
      }
      v = next[v][i];
    }
    return v;
  }

  void build() {
    lnk.assign(size(), 0);
    simple_queue<int> que;
    for (int i = 0; i < char_size; i++) {
      if (next[0][i] != -1) {
        que.push(next[0][i]);
      } else {
        next[0][i] = 0;
      }
    }
    while (!que.empty()) {
      int v = que.front();
      que.pop();
      for (int i = 0; i < char_size; i++) {
        int& u = next[v][i];
        if (u != -1) {
          lnk[u] = next[lnk[v]][i];
          que.push(u);
        } else {
          u = next[lnk[v]][i];
        }
      }
    }
  }

  const std::array<int, char_size>& operator[](int v) const {
    assert(0 <= v && v < int(next.size()));
    return next[v];
  }

  int parent(int v) const {
    assert(0 <= v && v < size());
    return par[v];
  }

  int link(int v) const {
    assert(0 <= v && v < size());
    return lnk[v];
  }

  int size() const { return int(next.size()); }

 private:
  std::vector<std::array<int, char_size>> next;
  std::vector<int> par;
  std::vector<int> lnk;
};

}  // namespace cp