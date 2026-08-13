#pragma once

#include <cstddef>
#include <iostream>
#include <vector>

#include "util/safe_hash.hpp"
#include "util/io_utility.hpp"

namespace cp {

template <class T> struct hash_set {
public:
  hash_set() : cap(8), sz(0), shift(61), keys(cap), used(cap) {}

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

  friend std::ostream& operator<<(std::ostream& os, const hash_set& s) {
    os << s.enumerate();
    return os;
  }

private:
  unsigned int cap, sz, shift;
  std::vector<T> keys;
  std::vector<bool> used;

  unsigned int index(const T& k) const {
    unsigned int hs = (unsigned int)(safe_hash<T>()(k) >> shift);
    while (used[hs] && keys[hs] != k) hs = (hs + 1) & (cap - 1);
    return hs;
  }

  void extend() {
    cap <<= 1;
    shift--;
    std::vector<T> k(cap);
    std::vector<bool> u(cap);
    for (int i = 0; i < int(keys.size()); i++) {
      if (!used[i]) continue;
      unsigned int hs = (unsigned int)(safe_hash<T>()(keys[i]) >> shift);
      while (u[hs]) hs = (hs + 1) & (cap - 1);
      k[hs] = keys[i];
      u[hs] = true;
    }
    keys.swap(k);
    used.swap(u);
  }
};

} // namespace cp