#pragma once

#include <algorithm>
#include <cctype>
#include <climits>
#include <iostream>
#include <string>

namespace cp {

std::istream& operator>>(std::istream& is, __int128& val) {
  std::string s;
  if (!(is >> s)) return is;
  val = 0;
  int i = (s[0] == '+' || s[0] == '-');
  while (i < int(s.size()) && std::isdigit(s[i])) {
    val = val * 10 + (s[i] - '0');
    i++;
  }
  if (s[0] == '-') val = -val;
  return is;
}

std::istream& operator>>(std::istream& is, unsigned __int128& val) {
  std::string s;
  if (!(is >> s)) return is;
  val = 0;
  int i = (s[0] == '+' || s[0] == '-');
  while (i < int(s.size()) && std::isdigit(s[i])) {
    val = val * 10 + (s[i] - '0');
    i++;
  }
  if (s[0] == '-') val = -val;
  return is;
}

std::ostream& operator<<(std::ostream& os, __int128 val) {
  if (LLONG_MIN <= val && val <= LLONG_MAX) {
    return os << (long long)(val);
  }
  unsigned __int128 uval = val;
  if (val < 0) {
    os << '-';
    uval = -val;
  }
  std::string s;
  while (uval) {
    s.push_back(char('0' + (uval % 10)));
    uval /= 10;
  }
  std::reverse(s.begin(), s.end());
  return os << s;
}

std::ostream& operator<<(std::ostream& os, unsigned __int128 val) {
  if (val <= ULLONG_MAX) {
    return os << (unsigned long long)(val);
  }
  std::string s;
  while (val) {
    s.push_back(char('0' + (val % 10)));
    val /= 10;
  }
  std::reverse(s.begin(), s.end());
  return os << s;
}

}  // namespace cp