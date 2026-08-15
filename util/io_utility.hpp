#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <charconv>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

namespace internal {

template <class T> char delimiter_after(const T& x) {
  if (is_integral_v<T>) return ' ';
  if (std::is_floating_point_v<T>) return ' ';
  if (std::ranges::range<T>) return '\n';
  if (is_tuple_v<T>) return '\n';
  if (std::is_same_v<T, std::string>) return '\n';

  std::ostringstream oss;
  oss << x;
  std::string s = oss.str();

  if (s.size() == 1) return ' ';

  {
    [[maybe_unused]] long long dummy;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), dummy);
    if (ec == std::errc{} && ptr == s.data() + s.size()) return ' ';
  }

  {
    [[maybe_unused]] long double dummy;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), dummy);
    if (ec == std::errc{} && ptr == s.data() + s.size()) return ' ';
  }

  return '\n';
}

} // namespace internal

} // namespace cp

namespace std {

// __int128

istream& operator>>(istream& is, __int128& val) {
  string s;
  if (is >> s) {
    val = 0;
    for (int i = (s[0] == '+' || s[0] == '-'); i < int(s.size()); i++) {
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
    for (int i = (s[0] == '+' || s[0] == '-'); i < int(s.size()); i++) {
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
  std::vector<T> v;
  v.assign(a.begin(), a.end());
  return os << v;
}

template <class T, class U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
  return os << std::make_tuple(p.first, p.second);
}

template <class... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t) {
  constexpr size_t n = sizeof...(Args);
  if (n == 0) return os;

  char delimiter = ' ';
  [&]<size_t... I>(index_sequence<I...>) {
    ([&](const auto& x) {
      if (cp::internal::delimiter_after(x) == '\n') {
        delimiter = '\n';
      }
    }(get<I>(t)), ...);
  }(make_index_sequence<n>());

  [&]<size_t... I>(index_sequence<I...>) {
    ([&](const auto& x) {
      os << x << delimiter;
    }(get<I>(t)), ...);
  }(make_index_sequence<n - 1>());

  return os << get<n - 1>(t);
}

template <class T, class Alloc>
ostream& operator<<(ostream& os, const vector<T, Alloc>& v) {
  if (v.empty()) return os;

  char delimiter = ' ';
  for (const auto& x : v) {
    if (cp::internal::delimiter_after(x) == '\n') {
      delimiter = '\n';
    }
  }

  for (int i = 0; i < int(v.size()) - 1; i++) {
    os << v[i] << delimiter;
  }
  return os << v.back();
}

} // namespace std