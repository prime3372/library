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

  bool count(const T& k) const { return d.get(k); }

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
    std::vector<std::string> outs;
    outs.reserve(s.size());
    auto elems = s.enumerate();
    std::ostringstream oss;
    for (auto& x : elems) {
      oss << x;
      outs.push_back(oss.str());
      oss.str("");
    }
    return os << internal::combine_outputs(outs);
  }

 private:
  int sz = 0;
  hash_map<T, char> d;
};

}  // namespace cp