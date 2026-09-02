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
    int& num = d[k];
    if (num == 0) return false;
    num--;
    sz--;
    return true;
  }

  int count(const T& k) const { return d.get(k); }

  std::vector<T> enumerate() const {
    auto pairs = d.enumerate();
    std::vector<T> res;
    for (auto& p : pairs) {
      while (p.second--) res.push_back(p.first);
    }
    return res;
  }

  int size() const { return sz; }

  friend std::ostream& operator<<(std::ostream& os, const hash_multiset& s) {
    using io_utility::operator<<;
    auto elems = s.enumerate();
    std::sort(elems.begin(), elems.end());
    return os << elems;
  }

 private:
  int sz = 0;
  hash_map<T, int> d;
};

}  // namespace cp