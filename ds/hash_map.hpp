#pragma once

#include <cassert>
#include <cstddef>
#include <functional>
#include <random>
#include <utility>
#include <vector>

#include "random/rng.hpp"

namespace cp {

template <class Key, class Val, class Hash = std::hash<Key>> struct hash_map {
public:
  hash_map() : cap(8), sz(0), shift(61), r(mt64()), keys(cap), vals(cap), used(cap), default_value() {}

  Val& operator[](Key k) {
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

  const Val& operator[](Key k) const {
    unsigned int i = index(k);
    return used[i] ? vals[i] : default_value;
  }

  Val& at(Key k) {
    unsigned int i = index(k);
    assert(used[i]);
    return vals[i];
  }

  const Val& at(Key k) const {
    unsigned int i = index(k);
    assert(used[i]);
    return vals[i];
  }

  bool count(Key k) const {
    unsigned int i = index(k);
    return used[i];
  }

  std::vector<std::pair<Key, Val>> enumerate() const {
    std::vector<std::pair<Key, Val>> res;
    for (unsigned int i = 0; i < cap; i++) {
      if (used[i]) res.emplace_back(keys[i], vals[i]);
    }
    return res;
  }

  int size() const { return int(sz); }

  void set_default(const Val& v) { default_value = v; }

private:
  static Hash hasher;
  unsigned int cap, sz, shift;
  unsigned long long r;
  std::vector<Key> keys;
  std::vector<Val> vals;
  std::vector<bool> used;
  Val default_value;

  unsigned int get_hash(Key k) const { return (unsigned int)((hasher(k) * r) >> shift); }

  unsigned int index(Key k) const {
    unsigned int hs = get_hash(k);
    while (used[hs] && keys[hs] != k) hs = (hs + 1) & (cap - 1);
    return hs;
  }

  void extend() {
    cap <<= 1;
    shift--;
    std::vector<Key> k(cap);
    std::vector<Val> v(cap);
    std::vector<bool> u(cap);
    for (int i = 0; i < int(keys.size()); i++) {
      if (!used[i]) continue;
      unsigned int hs = get_hash(keys[i]);
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

} // namespace cp