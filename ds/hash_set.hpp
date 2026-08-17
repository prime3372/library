#pragma once

#include <cstddef>
#include <iostream>
#include <vector>

#include "util/safe_hash.hpp"

namespace cp {

template <class T> struct hash_set {
 public:
  hash_set() : cap(8), sz(0), keys(cap), used(cap) {}

  bool insert(const T& k) {
    unsigned int i = index(k);
    if (used[i]) return false;
    if (sz + sz / 4 >= cap) {
      extend();
      return insert(k);
    }
    keys[i] = k;
    used[i] = true;
    sz++;
    return true;
  }

  bool count(const T& k) const {
    unsigned int i = index(k);
    return used[i];
  }

  std::vector<T> enumerate() const {
    std::vector<T> res;
    for (unsigned int i = 0; i < cap; i++) {
      if (used[i]) res.push_back(keys[i]);
    }
    return res;
  }

  int size() const { return sz; }

 private:
  unsigned int cap, sz;
  std::vector<T> keys;
  std::vector<bool> used;

  unsigned int hash(const T& k) {
    return (unsigned int)(safe_hash<T>()(k) & (cap - 1));
  }

  unsigned int index(const T& k) const {
    unsigned int hs = hash(k);
    while (used[hs] && keys[hs] != k) hs = (hs + 1) & (cap - 1);
    return hs;
  }

  void extend() {
    cap <<= 1;
    std::vector<T> k(cap);
    std::vector<bool> u(cap);
    for (int i = 0; i < int(keys.size()); i++) {
      if (!used[i]) continue;
      unsigned int hs = hash(keys[i]);
      while (u[hs]) hs = (hs + 1) & (cap - 1);
      k[hs] = keys[i];
      u[hs] = true;
    }
    keys.swap(k);
    used.swap(u);
  }
};

} // namespace cp