#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace cp {

class union_find {
 public:
  union_find() : n(0), cnt(0) {}
  explicit union_find(int _n) : n(_n), cnt(_n), par_size(_n, -1) {}

  bool unite(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (-par_size[a] < -par_size[b]) std::swap(a, b);
    par_size[a] += par_size[b];
    par_size[b] = a;
    cnt--;
    return true;
  }

  int find(int a) {
    assert(0 <= a && a < n);
    return _find(a);
  }

  bool same(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    return find(a) == find(b);
  }

  int size(int a) {
    assert(0 <= a && a < n);
    return -par_size[find(a)];
  }

  int size() const { return n; }

  int count() const { return cnt; }

  std::vector<std::vector<int>> groups() {
    std::vector<int> root(n);
    for (int i = 0; i < n; i++) {
      root[i] = find(i);
    }
    std::vector<std::vector<int>> res(n);
    for (int i = 0; i < n; i++) {
      res[root[i]].push_back(i);
    }
    res.erase(
        std::remove_if(res.begin(), res.end(),
                       [&](const std::vector<int>& v) { return v.empty(); }),
        res.end());
    return res;
  }

 private:
  int n, cnt;
  // root node: -1 * component size
  // otherwise: parent
  std::vector<int> par_size;
  int _find(int a) {
    if (par_size[a] < 0) return a;
    return par_size[a] = _find(par_size[a]);
  }
};

}  // namespace cp