#pragma once

#include <cassert>
#include <cctype>
#include <iostream>
#include <string>

#include "util/io_int128.hpp"

namespace cp {

// fixed-point format only
std::istream& operator>>(std::istream& is, __float128& val) {
  std::string s;
  if (!(is >> s)) return is;
  val = 0;
  int i = (s[0] == '+' || s[0] == '-');
  __float128 p10 = 1;
  bool has_dec = false;
  while (i < int(s.size()) && (std::isdigit(s[i]) || s[i] == '.')) {
    if (s[i] == '.') {
      has_dec = true;
    } else {
      val = val * 10 + (s[i] - '0');
      if (has_dec) p10 *= 10;
    }
    i++;
  }
  val /= p10;
  if (s[0] == '-') val = -val;
  return is;
}

// output in fixed-point format
std::ostream& operator<<(std::ostream& os, __float128 x) {
  assert(!__builtin_isnan(x) && !__builtin_isinf(x));
  int prec = int(os.precision());

  if (x < 0) {
    os << '-';
    x = -x;
  }

  __float128 r = 1;
  for (int i = 0; i < prec; i++) r *= 10;
  x += __float128(0.5) / r;

  int int_len = 0;
  while (x >= 1) {
    x /= 10;
    int_len++;
  }
  for (int i = 0; i < int_len; i++) {
    x *= 10;
    os << int(x);
    x -= int(x);
  }
  if (int_len == 0) os << 0;

  if (prec > 0) {
    os << '.';
    for (int i = 0; i < prec; i++) {
      x *= 10;
      os << int(x);
      x -= int(x);
    }
  }

  return os;
}

}  // namespace cp