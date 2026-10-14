#pragma once

#include <string>
#include <utility>
#include <vector>

#include "ds/hash-map.hpp"

namespace cp {

template <class T> struct HashSet {
 public:
  HashSet() {}

  bool insert(const T& k) {
    char& f = d[k];
    if (f) return false;
    sz++;
    f = true;
    return true;
  }

  template <class... Args> bool emplace(Args&&... args) {
    return insert(T(std::forward<Args>(args)...));
  }

  bool erase(const T& k) {
    char& f = d[k];
    if (!f) return false;
    sz--;
    f = false;
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

 private:
  int sz = 0;
  HashMap<T, char> d;
};

}  // namespace cp