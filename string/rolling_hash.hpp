#pragma once

#include <cassert>
#include <vector>

#include "random/common.hpp"
#include "util/hash61.hpp"

namespace cp {

template <class Str> struct rolling_hash {
public:
  rolling_hash() : rolling_hash(Str()) {}
  explicit rolling_hash(const Str& s) : n(int(s.size())) {
    hs.resize(n + 1);
    pw.resize(n + 1);
    pw[0] = 1;
    for (int i = 0; i < n; i++) {
      hs[i + 1] = hs[i] * basis + (hash61)((unsigned long long)(s[i]) ^ rnd);
      pw[i + 1] = pw[i] * basis;
    }
  }

  hash61 get(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return hs[r] - hs[l] * pw[r - l];
  }

  static hash61 to_hash(const Str& s) {
    hash61 h = 0;
    for (int i = 0; i < int(s.size()); i++) {
      h = h * basis + (hash61)((unsigned long long)(s[i]) ^ rnd);
    }
    return h;
  }

private:
  static hash61 basis;
  static unsigned long long rnd;
  int n;
  std::vector<hash61> hs, pw;
};

template <class Str> hash61 rolling_hash<Str>::basis = hash61::get_basis();
template <class Str> unsigned long long rolling_hash<Str>::rnd = mt64();

} // namespace cp