#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "util/type_traits.hpp"

namespace std {

istream& operator>>(istream& is, __int128& val) {
  string s;
  if (is >> s) {
    val = 0;
    for (int i = s[0] == '+' || s[0] == '-'; i < int(s.size()); i++) {
      if (!isdigit(s[i])) break;
      val = val * 10 + (s[i] - '0');
    }
    if (s[0] == '-') val = -val;
  }
  return is;
}

istream& operator>>(istream& is, unsigned __int128& val) {
  string s;
  if (is >> s) {
    val = 0;
    for (int i = s[0] == '+' || s[0] == '-'; i < int(s.size()); i++) {
      if (!isdigit(s[i])) break;
      val = val * 10 + (s[i] - '0');
    }
    if (s[0] == '-') val = ~val + 1;
  }
  return is;
}

ostream& operator<<(ostream& os, __int128 val) {
  if (val == 0) return os << '0';
  unsigned __int128 uval = val;
  if (val < 0) {
    os << '-';
    uval = -val;
  }
  string s;
  while (uval) {
    s.push_back((char)('0' + (uval % 10)));
    uval /= 10;
  }
  reverse(s.begin(), s.end());
  return os << s;
}

ostream& operator<<(ostream& os, unsigned __int128 val) {
  if (val == 0) return os << '0';
  string s;
  while (val) {
    s.push_back((char)('0' + (val % 10)));
    val /= 10;
  }
  reverse(s.begin(), s.end());
  return os << s;
}

template <class Tuple> requires cp::is_tuple_like_v<Tuple>
istream& operator>>(istream& is, Tuple& t);

template <class Tuple> requires cp::is_tuple_like_v<Tuple>
ostream& operator<<(ostream& os, const Tuple& t);

template <class T>
istream& operator>>(istream& is, vector<T>& v);

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v);

template <class T>
istream& operator>>(istream& is, vector<T>& v) {
  for (auto& x : v) is >> x;  
  return is;
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  for (int i = 0; i < int(v.size()); i++) {
    os << v[i];
    if (i != int(v.size()) - 1) {
      if constexpr (cp::is_tuple_like_v<T> || cp::is_vector_v<T>) {
        os << "\n";
      } else {
        os << " ";
      }
    }
  }
  return os;
}

} // namespace std