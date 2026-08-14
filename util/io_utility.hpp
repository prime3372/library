#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

namespace internal {

template <class T> struct delimiter_of {
  static constexpr char value = '\n';
};

template <class T>
inline constexpr char delimiter_of_v = delimiter_of<T>::value;

template <class T> requires is_integral_v<std::decay_t<T>>
struct delimiter_of<T> {
  static constexpr char value = ' ';
};

template <class T> requires std::is_floating_point_v<std::decay_t<T>>
struct delimiter_of<T> {
  static constexpr char value = ' ';
};

template <class T> requires is_modint_v<std::decay_t<T>>
struct delimiter_of<T> {
  static constexpr char value = ' ';
};

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

// utilities for input

template <class T, size_t Size>
istream& operator>>(istream& is, array<T, Size>& a);

template <class T, class U>
istream& operator>>(istream& is, pair<T, U>& p);

template <class... Args>
istream& operator>>(istream& is, tuple<Args...>& t);

template <class T, class Alloc>
istream& operator>>(istream& is, vector<T, Alloc>& v);

template <class T, size_t Size>
istream& operator>>(istream& is, array<T, Size>& a) {
  for (auto& x : a) is >> x;
  return is;
}

template <class T, class U>
istream& operator>>(istream& is, pair<T, U>& p) {
  return is >> p.first >> p.second;
}

template <class... Args>
istream& operator>>(istream& is, tuple<Args...>& t) {
  [&]<size_t... I>(index_sequence<I...>) {
    (is >> ... >> get<I>(t));
  }(make_index_sequence<sizeof...(Args)>());
  return is;
}

template <class T, class Alloc>
istream& operator>>(istream& is, vector<T, Alloc>& v) {
  for (auto& x : v) is >> x;
  return is;
}

// utilities for output

template <class T, size_t Size>
ostream& operator<<(ostream& os, const array<T, Size>& a);

template <class T, class U>
ostream& operator<<(ostream& os, const pair<T, U>& p);

template <class... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t);

template <class T, class Alloc>
ostream& operator<<(ostream& os, const vector<T, Alloc>& v);

template <class T, size_t Size>
ostream& operator<<(ostream& os, const array<T, Size>& a) {
  for (int i = 0; i < int(a.size()); i++) {
    os << a[i];
    if (i != int(a.size()) - 1) {
      os << cp::internal::delimiter_of_v<T>;
    }
  }
  return os;
}

template <class T, class U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
  constexpr char delimiter =
    cp::internal::delimiter_of_v<T> == '\n' ? '\n' :
    cp::internal::delimiter_of_v<U> == '\n' ? '\n' : ' ';
  return os << p.first << delimiter << p.second;
}

template <class... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t) {
  constexpr size_t n = sizeof...(Args);
  if (n == 0) return os;

  constexpr char delimiter = []{
    char res = ' ';
    ((res = cp::internal::delimiter_of_v<Args> == '\n' ? '\n' : res), ...);
    return res;
  }();

  [&]<size_t... I>(index_sequence<I...>) {
    ([&]<class T>(const T& x) {
      os << x << delimiter;
    }(get<I>(t)), ...);
  }(make_index_sequence<n - 1>());

  return os << get<n - 1>(t);
}

template <class T, class Alloc>
ostream& operator<<(ostream& os, const vector<T, Alloc>& v) {
  for (int i = 0; i < int(v.size()); i++) {
    os << v[i];
    if (i != int(v.size()) - 1) {
      os << cp::internal::delimiter_of_v<T>;
    }
  }
  return os;
}

} // namespace std