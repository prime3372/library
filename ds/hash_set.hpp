#pragma once

#include <vector>

#include "ds/hash_map.hpp"

namespace cp {

template <class T> struct hash_set {
public:
  hash_set() {}

  void insert(const T& x) { mp[x]; }

  bool count(const T& x) const { return mp.count(x); }

  std::vector<T> enumerate() const {
    auto pairs = mp.enumerate();
    std::vector<T> res(e.size());
    for (int i = 0; i < int(pairs.size()); i++) {
      res[i] = pairs[i].first;
    }
    return res;
  }

  int size() const { return mp.size(); }

private:
  hash_map<T, char> mp;
};

} // namespace cp