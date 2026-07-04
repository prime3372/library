#pragma once

#include <cassert>
#include <vector>

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
      hs[i + 1] = hs[i] * basis + s[i];
      pw[i + 1] = pw[i] * basis;
    }
  }

  static hash61 get_hash(const Str& s) {
    hash61 h;
    for (int i = 0; i < int(s.size()); i++) {
      h = h * basis + s[i];
    }
    return h;
  }

  hash61 get(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return hs[r] - hs[l] * pw[r - l];
  }

private:
  int n;
  std::vector<hash61> hs, pw;
  inline static hash61 basis = [](){ return hash61::get_base(); }();
};

} // namespace cp