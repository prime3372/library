#pragma once

#include <cstddef>
#include <iostream>
#include <vector>

#include "ds/hash_map.hpp"

namespace cp {

template <class T> class hash_multiset {
 public:
  hash_multiset() {}

  void insert(const T& k) {
    d[k]++;
    sz++;
  }

  bool erase(const T& k) {
    int& cnt = d[k];
    if (cnt == 0) return false;
    cnt--;
    sz--;
    return true;
  }

  int count(const T& k) { return d[k]; }

  std::vector<T> enumerate() {
    auto pairs = d.enumerate();
    std::vector<T> res;
    for (const auto& p : pairs) {
      for (int i = 0; i < p.second; i++) {
        res.push_back(p.first);
      }
    }
    return res;
  }

  int size() { return sz; }

 private:
  int sz = 0;
  hash_map<T, int> d;
};

}  // namespace cp