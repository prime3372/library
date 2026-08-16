#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <charconv>
#include <cstddef>
#include <iostream>
#include <queue>
#include <ranges>
#include <sstream>
#include <stack>
#include <type_traits>
#include <utility>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

namespace internal {

template <class T> struct delimiter_of {
  char operator()(const T& x) {
    if (is_integral_v<T>) return ' ';
    if (std::is_floating_point_v<T>) return ' ';

    std::ostringstream oss;
    oss << x;
    std::string s = oss.str();

    if (s.size() == 1) return ' ';

    long double dummy;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), dummy);
    if (ec == std::errc{} && ptr == s.data() + s.size()) return ' ';

    return '\n';
  }
};

template <> struct delimiter_of<std::string> {
  char operator()(const std::string&) { return '\n'; }
};

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

template <ranges::range Range>
  requires (!is_convertible_v<Range, string>)
ostream& operator<<(ostream& os, const Range& r) {
  if (r.empty()) return os;

  char delimiter = ' ';
  for (const auto& x : r) {
    using cp::internal::delimiter_of;
    if (delimiter_of<std::decay_t<decltype(x)>>()(x) == '\n') {
      delimiter = '\n';
    }
  }

  bool first = true;
  for (const auto& x : r) {
    if (!first) os << delimiter;
    os << x;
    first = false;
  }
  return os;
}

template <class T, class Container>
ostream& operator<<(ostream& os, queue<T, Container> q) {
  vector<T> v(q.size());
  int i = 0;
  while (!q.empty()) {
    v[i++] = q.front();
    q.pop();
  }
  return os << v;
}

template <class T, class Container, class Compare>
ostream& operator<<(ostream& os, priority_queue<T, Container, Compare> pq) {
  vector<T> v(pq.size());
  int i = 0;
  while (!pq.empty()) {
    v[i++] = pq.top();
    pq.pop();
  }
  return os << v;
}

template <class T, class Container>
ostream& operator<<(ostream& os, stack<T, Container> st) {
  vector<T> v(st.size());
  int i = 0;
  while (!st.empty()) {
    v[i++] = st.top();
    st.pop();
  }
  return os << v;
}

template <class T, class U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
  return os << tie(p.first, p.second);
}

template <class... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t) {
  constexpr size_t n = sizeof...(Args);
  if (n == 0) return os;

  char delimiter = ' ';
  [&]<size_t... I>(index_sequence<I...>) {
    ([&](const auto& x) {
      using cp::internal::delimiter_of;
      if (delimiter_of<decay_t<decltype(x)>>()(x) == '\n') {
        delimiter = '\n';
      }
    }(get<I>(t)), ...);
  }(make_index_sequence<n>());

  apply([&](const auto&... args) {
    bool first = true;
    ((first ? (os << args) : (os << delimiter << args), first = false), ...);
  }, t);

  return os;
}

} // namespace std