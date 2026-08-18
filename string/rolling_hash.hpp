#pragma once

#include <cassert>
#include <type_traits>
#include <vector>

#include "random/base.hpp"
#include "util/hash61.hpp"
#include "util/safe_hash.hpp"

namespace cp {

class rolling_hash {
 public:
  rolling_hash() : n(-1) {}
  template <class Str> explicit rolling_hash(const Str& s) : n(int(s.size())) {
    hs.resize(n + 1);
    pw.resize(n + 1);
    pw[0] = 1;
    for (int i = 0; i < n; i++) {
      hs[i + 1] = hs[i] * basis + hash_char(s[i]);
      pw[i + 1] = pw[i] * basis;
    }
  }

  hash61 get(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return hs[r] - hs[l] * pw[r - l];
  }

  template <class Str> static hash61 to_hash(const Str& s) {
    hash61 h = 0;
    for (int i = 0; i < int(s.size()); i++) {
      h = h * basis + hash_char(s[i]);
    }
    return h;
  }

 private:
  static hash61 basis;
  int n;
  std::vector<hash61> hs, pw;

  template <class T> unsigned long long hash_char(const T& c) {
    return safe_hash<T>()(c);
  }
};

hash61 rolling_hash::basis = hash61::get_basis();

}  // namespace cp