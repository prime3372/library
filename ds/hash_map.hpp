#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "util/io_utility_base.hpp"
#include "util/safe_hash.hpp"

namespace cp {

// @note `Val` cannot be `bool`
template <class Key, class Val> class hash_map {
 public:
  hash_map()
      : cap(8), sz(0), keys(cap), vals(cap), used(cap), default_value() {}

  Val& operator[](const Key& k) {
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

  const Val& get(const Key& k) const {
    unsigned int i = index(k);
    return used[i] ? vals[i] : default_value;
  }

  bool count(const Key& k) const {
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

  int size() const { return sz; }

  void set_default(const Val& v) { default_value = v; }

  friend std::ostream& operator<<(std::ostream& os, const hash_map& mp) {
    using io_utility::operator<<;
    auto elems = mp.enumerate();
    std::sort(elems.begin(), elems.end());
    os << elems;
  }

 private:
  unsigned int cap, sz;
  std::vector<Key> keys;
  std::vector<Val> vals;
  std::vector<bool> used;
  Val default_value;

  unsigned int hash(const Key& k) const {
    return (unsigned int)(safe_hash<Key>()(k) & (cap - 1));
  }

  unsigned int index(const Key& k) const {
    unsigned int hs = hash(k);
    while (used[hs] && keys[hs] != k) hs = (hs + 1) & (cap - 1);
    return hs;
  }

  void extend() {
    cap <<= 1;
    std::vector<Key> k(cap);
    std::vector<Val> v(cap);
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

}  // namespace cp