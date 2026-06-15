#pragma once

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

std::istream& operator>>(std::istream& is, __int128& val) {
  std::string s;
  if (is >> s) {
    val = 0;
    bool is_negative = s[0] == '-';
    bool starts_from_sign = s[0] == '+' || s[0] == '-';
    for (int i = starts_from_sign; i < int(s.size()); i++) {
      if (!std::isdigit(s[i])) break;
      val = val * 10 + (s[i] - '0');
    }
    if (is_negative) val = -val;
  }
  return is;
}

std::istream& operator>>(std::istream& is, unsigned __int128& val) {
  std::string s;
  if (is >> s) {
    val = 0;
    bool is_negative = s[0] == '-';
    bool starts_from_sign = s[0] == '+' || s[0] == '-';
    for (int i = starts_from_sign; i < int(s.size()); i++) {
      if (!std::isdigit(s[i])) break;
      val = val * 10 + (s[i] - '0');
    }
    if (is_negative) val = -val;
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, __int128 val) {
  if (val == 0) return os << '0';
  unsigned __int128 uval = val;
  if (val < 0) {
    os << '-';
    uval = -val;
  }
  std::string s;
  while (uval) {
    s.push_back((char)('0' + (uval % 10)));
    uval /= 10;
  }
  std::reverse(s.begin(), s.end());
  return os << s;
}

std::ostream& operator<<(std::ostream& os, unsigned __int128 val) {
  if (val == 0) return os << '0';
  std::string s;
  while (val) {
    s.push_back((char)('0' + (val % 10)));
    val /= 10;
  }
  std::reverse(s.begin(), s.end());
  return os << s;
}
