#pragma once

#include "ds/hash_map.hpp"

namespace cp {

template <class T> struct hash_set {
public:
  void insert(const T& x) { mp[x]; }
  bool count(const T& x) const { return mp.count(x); }
private:
  hash_map<T, char> mp;
};

} // namespace cp