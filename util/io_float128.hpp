#pragma once

#include <cassert>
#include <cctype>
#include <iostream>
#include <string>

#include "util/io_int128.hpp"

namespace cp {

// @note fixed-point format only
std::istream& operator>>(std::istream& is, __float128& val) {
  std::string s;
  if (!(is >> s)) return is;

  val = 0;
  __float128 p10 = 1;
  bool has_dec = false;

  int i = (s[0] == '+' || s[0] == '-');
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

// @note output in fixed-point format
std::ostream& operator<<(std::ostream& os, __float128 x) {
  assert(!__builtin_isnan(x) && !__builtin_isinf(x));
  const int prec = int(os.precision());

  if (x < 0) {
    os << '-';
    x = -x;
  }

  __float128 p10 = 1;
  for (int i = 0; i < prec; i++) p10 *= 10;
  x += (__float128)(0.5) / p10;

  unsigned __int128 int_part = (unsigned __int128)(x);
  os << int_part;
  x -= (__float128)int_part;

  if (prec > 0) {
    os << '.';
    for (int i = 0; i < prec; i++) {
      x *= 10;
      int d = int(x);
      if (d > 9) d = 9;
      if (d < 0) d = 0;
      os << d;
      x -= d;
    }
  }

  return os;
}

}  // namespace cp