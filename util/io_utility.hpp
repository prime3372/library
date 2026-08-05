#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

namespace internal {

template <class T> void output_delimiter(std::ostream& os) {
  if constexpr (is_tuple_like_v<T> || is_vector_v<T>) {
    os << "\n";
  } else {
    os << " ";
  }
}

} // namespace internal

} // namespace cp

namespace std {

// __int128

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

// forward declarations

template <class Tuple> requires cp::internal::is_tuple_like_v<Tuple>
istream& operator>>(istream& is, Tuple& t);

template <class Tuple> requires cp::internal::is_tuple_like_v<Tuple>
ostream& operator<<(ostream& os, const Tuple& t);

template <class T>
istream& operator>>(istream& is, vector<T>& v);

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v);

// tuple_like (array, tuple, pair)

template <class Tuple> requires cp::internal::is_tuple_like_v<Tuple>
istream& operator>>(istream& is, Tuple& t) {
  apply([&](auto&... args) {
    (is >> ... >> args);
  }, t);
  return is;
}

template <class Tuple> requires cp::internal::is_tuple_like_v<Tuple>
ostream& operator<<(ostream& os, const Tuple& t) {
  static constexpr size_t n = tuple_size_v<Tuple>; 
  if constexpr (n == 0) return os;
  [&]<size_t... I>(index_sequence<I...>) {
    ([&]<class T>(const T& x) {
      os << x;
      cp::internal::output_delimiter<T>(os);
    }(get<I>(t)), ...);
  }(make_index_sequence<n - 1>());
  os << get<n - 1>(t);
  return os;
}

// vector

template <class T>
istream& operator>>(istream& is, vector<T>& v) {
  for (T& x : v) is >> x;  
  return is;
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  for (int i = 0; i < int(v.size()); i++) {
    os << v[i];
    if (i != int(v.size()) - 1) {
      cp::internal::output_delimiter<T>(os);
    }
  }
  return os;
}

} // namespace std