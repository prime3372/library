#pragma once  
  
#include <string>

#include "random/rng.hpp"

namespace cp {

template <bool upper = false> std::string random_str(int n) {
  std::string res(n, 0);
  for (int i = 0; i < n; i++) {
    res[i] = char((upper ? 'A' : 'a') + mt32() % 26);
  }
  return res;
}

std::string random_str(int n, std::string s) {
  std::string res(n, 0);
  for (int i = 0; i < n; i++) {
    res[i] = s[mt32() % s.size()];
  }
  return res;
}

std::string random_dec(int n) {
  return random_str(n, "0123456789");
}

} // namespace cp