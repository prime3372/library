#pragma once

#include <cassert>
#include <cstddef>
#include <random>
#include <utility>
#include <vector>
#include "random/rng.hpp"

template <class T> struct hash_map {
public:
  hash_map() : cap(8), sz(0), keys(cap), vals(cap), used(cap), r(mt64()), shift(61), default_value(T()) {}

  T& operator[](size_t k) {
    unsigned int i = index(k);
    if (used[i]) return vals[i];
    if (sz + sz / 4 >= cap) {
      extend();
      return (*this)[k];
    }
    keys[i] = k;
    used[i] = true;
    sz++;
    return vals[i] = default_value;
  }

  T operator[](size_t k) const {
    unsigned int i = index(k);
    return used[i] ? vals[i] : default_value;
  }

  bool count(size_t k) const {
    unsigned int i = index(k);
    return used[i];
  }

  std::vector<std::pair<size_t, T>> enumerate() const {
    std::vector<std::pair<size_t, T>> res;
    for (unsigned int i = 0; i < cap; i++) {
      if (used[i]) res.emplace_back(keys[i], vals[i]);
    }
    return res;
  }

  int size() const { return int(sz); }

  void set_default(const T& v) { default_value = v; }

private:
  unsigned int cap, sz;
  std::vector<size_t> keys;
  std::vector<T> vals;
  std::vector<bool> used;
  unsigned long long r;
  unsigned int shift;
  T default_value;

  unsigned int hash(size_t k) const { return (k * r) >> shift; }

  size_t index(size_t k) const {
    unsigned int hs = hash(k);
    while (used[hs] && keys[hs] != k) hs = (hs + 1) & (cap - 1);
    return hs;
  }

  void extend() {
    cap <<= 1;
    shift--;
    std::vector<size_t> k(cap);
    std::vector<T> v(cap);
    std::vector<bool> u(cap);
    for (int i = 0; i < int(keys.size()); i++) {
      if (!used[i]) continue;
      unsigned int hs = hash(keys[i]);
      while (u[hs]) hs = (hs + 1) & (cap - 1);
      k[hs] = keys[i];
      v[hs] = vals[i];
      u[hs] = true;
    }
    keys.swap(k);
    vals.swap(v);
    used.swap(u);
  }
};
