#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "ds/union_find.hpp"

namespace cp {

class enumeratable_union_find : public union_find {
 public:
  using union_find::size;

  enumeratable_union_find() {}
  explicit enumeratable_union_find(int _n) : nxt(_n) {
    for (int i = 0; i < _n; i++) nxt[i] = i;
  }

  template <class F> bool unite(int a, int b, F f) {
    assert(0 <= a && a < size());
    assert(0 <= b && b < size());
    if (unite(a, b)) f(a, b);
  }

  std::vector<int> enumerate(int a) const {
    assert(0 <= a && a < size());
    std::vector<int> res = {a};
    for (int i = nxt[a]; i != a; i = nxt[i]) {
      res.push_back(i);
    }
    return res;
  }

 private:
  std::vector<int> nxt;
};

}  // namespace cp