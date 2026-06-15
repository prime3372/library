#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

struct rollback_union_find {
public:
  rollback_union_find() : rollback_union_find(0) {}
  explicit rollback_union_find(int _n) : n(_n), inner_snap(0), parent_or_size(_n, -1) {}

  int unite(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = find(a);
    b = find(b);
    history.emplace_back(a, parent_or_size[a]);
    history.emplace_back(b, parent_or_size[b]);
    if (a == b) return a;
    if (-parent_or_size[a] < -parent_or_size[b]) std::swap(a, b);
    parent_or_size[a] += parent_or_size[b];
    parent_or_size[b] = a;
    return a;
  }

  int find(int a) {
    assert(0 <= a && a < n);
    while (parent_or_size[a] >= 0) a = parent_or_size[a];
    return a;
  }
  
  bool same(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    return find(a) == find(b);
  }
  
  int size(int a) {
    assert(0 <= a && a < n);
    return -parent_or_size[find(a)];
  }

  void undo() {
    parent_or_size[history.back().first] = history.back().second;
    history.pop_back();
    parent_or_size[history.back().first] = history.back().second;
    history.pop_back();
  }

  void snapshot() { inner_snap = int(history.size()); }
  void rollback() { while (inner_snap < int(history.size())) undo(); }

  std::vector<std::vector<int>> groups() {
    std::vector<int> root(n), group_size(n);
    for (int i = 0; i < n; i++) {
      root[i] = find(i);
      group_size[root[i]]++;
    }
    std::vector<std::vector<int>> res(n);
    for (int i = 0; i < n; i++) {
      res[i].reserve(group_size[i]);
    }
    for (int i = 0; i < n; i++) {
      res[root[i]].push_back(i);
    }
    res.erase(std::remove_if(res.begin(), res.end(),
                             [&](const std::vector<int>& v) { return v.empty(); }),
              res.end());
    return res;
  }

private:
  int n, inner_snap;
  std::vector<int> parent_or_size;
  std::vector<std::pair<int, int> > history;
};
