#pragma once  

#include <cassert>
#include <string>

#include "random/rng.hpp"

namespace cp {

template <bool upper = false> std::string random_str(int n) {
  assert(0 <= n);
  std::string res(n, 0);
  for (int i = 0; i < n; i++) {
    res[i] = char((upper ? 'A' : 'a') + mt32() % 26);
  }
  return res;
}

std::string random_str(int n, std::string s) {
  assert(0 <= n);
  std::string res(n, 0);
  for (int i = 0; i < n; i++) {
    res[i] = s[mt32() % s.size()];
  }
  return res;
}

std::string random_dec(int n) {
  assert(0 <= n);
  if (n == 0) return "";
  else return random_str(1, "123456789") + random_str(n - 1, "0123456789");
}

} // namespace cp