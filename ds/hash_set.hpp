#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ds/hash_map.hpp"

namespace cp {

template <class T> class hash_set {
 public:
  hash_set() {}

  bool insert(const T& k) {
    char& f = d[k];
    return f ? false : (sz++, f = true);
  }

  bool erase(const T& k) {
    char& f = d[k];
    return f ? (sz--, !(f = false)) : false;
  }

  int count(const T& k) const { return d.get(k); }
  bool contains(const T& k) const { return count(k); }

  std::vector<T> enumerate() const {
    auto pairs = d.enumerate();
    std::vector<T> res;
    for (auto& p : pairs) {
      if (p.second) res.push_back(p.first);
    }
    return res;
  }

  int size() const { return sz; }

  friend std::ostream& operator<<(std::ostream& os, const hash_set& s) {
    using io_utility::operator<<;
    auto elems = s.enumerate();
    std::sort(elems.begin(), elems.end());
    return os << elems;
  }

 private:
  int sz = 0;
  hash_map<T, char> d;
};

}  // namespace cp