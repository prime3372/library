#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

std::istream& operator>>(std::istream& is, __int128& val) {
  std::string s;
  if (is >> s) {
    val = 0;
    for (int i = s[0] == '+' || s[0] == '-'; i < int(s.size()); i++) {
      if (!std::isdigit(s[i])) break;
      val = val * 10 + (s[i] - '0');
    }
    if (s[0] == '-') val = -val;
  }
  return is;
}

std::istream& operator>>(std::istream& is, unsigned __int128& val) {
  std::string s;
  if (is >> s) {
    val = 0;
    for (int i = s[0] == '+' || s[0] == '-'; i < int(s.size()); i++) {
      if (!std::isdigit(s[i])) break;
      val = val * 10 + (s[i] - '0');
    }
    if (s[0] == '-') val = ~val + 1;
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

template <class T, class U>
std::istream& operator>>(std::istream& is, std::pair<T, U>& p);

template <class T, class U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p);

template <class T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
  for (auto& x : v) is >> x;  
  return is;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  for (int i = 0; i < int(v.size()); i++) {
    os << v[i];
    if (i != int(v.size()) - 1) {
      if constexpr (is_pair_v<T> || is_vector_v<T>) {
        os << "\n";
      } else {
        os << " ";
      }
    }
  }
  return os;
}

template <class T, class U>
std::istream& operator>>(std::istream& is, std::pair<T, U>& p) {
  is >> p.first >> p.second;
  return is;
}

template <class T, class U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
  os << p.first;
  if constexpr (is_pair_v<T> || is_vector_v<T>) {
    os << "\n";
  } else {
    os << " ";
  }
  os << p.second;
  return os;
}

} // namespace cp