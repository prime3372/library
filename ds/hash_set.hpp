#pragma once

#include <cstddef>
#include <iostream>
#include <vector>

#include "ds/hash_map.hpp"

namespace cp {

template <class T> class hash_set {
 public:
  hash_set() {}

  bool insert(const T& k) {
    char& flag = d[k];
    if (flag) return false;
    flag = true;
    sz++;
    return true;
  }

  bool erase(const T& k) {
    char& flag = d[k];
    if (!flag) return false;
    flag = false;
    sz--;
    return true;
  }

  bool count(const T& k) { return d[k]; }

  std::vector<T> enumerate() {
    auto pairs = d.enumerate();
    std::vector<T> res;
    for (auto& p : pairs) {
      if (p.second) res.push_back(p.first);
    }
    return res;
  }

  int size() { return sz; }

 private:
  int sz = 0;
  hash_map<T, char> d;
};

}  // namespace cp