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

std::istream& operator>>(std::istream& is, __int128& val);

std::istream& operator>>(std::istream& is, unsigned __int128& val);

template <class T, size_t Size>
std::istream& operator>>(std::istream& is, std::array<T, Size>& a);

template <class T, class U>
std::istream& operator>>(std::istream& is, std::pair<T, U>& p);

template <class... Args>
std::istream& operator>>(std::istream& is, std::tuple<Args...>& t);

template <class T, class Alloc>
std::istream& operator>>(std::istream& is, std::vector<T, Alloc>& v);

std::istream& operator>>(std::istream& is, __int128& val) {
  std::string s;
  if (is >> s) {
    val = 0;
    for (int i = (s[0] == '+' || s[0] == '-'); i < int(s.size()); i++) {
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
    for (int i = (s[0] == '+' || s[0] == '-'); i < int(s.size()); i++) {
      if (!std::isdigit(s[i])) break;
      val = val * 10 + (s[i] - '0');
    }
    if (s[0] == '-') val = ~val + 1;
  }
  return is;
}

template <class T, size_t Size>
std::istream& operator>>(std::istream& is, std::array<T, Size>& a) {
  for (auto& x : a) is >> x;
  return is;
}

template <class T, class U>
std::istream& operator>>(std::istream& is, std::pair<T, U>& p) {
  return is >> p.first >> p.second;
}

template <class... Args>
std::istream& operator>>(std::istream& is, std::tuple<Args...>& t) {
  std::apply([&](auto&... args) { (is >> ... >> args); }, t);
  return is;
}

template <class T, class Alloc>
std::istream& operator>>(std::istream& is, std::vector<T, Alloc>& v) {
  for (auto& x : v) is >> x;
  return is;
}

std::ostream& operator<<(std::ostream& os, __int128 val);

std::ostream& operator<<(std::ostream& os, unsigned __int128 val);

template <std::ranges::range Range>
requires(!std::is_convertible_v<Range, std::string>)
std::ostream& operator<<(std::ostream& os, const Range& r);

template <class T, class Container>
std::ostream& operator<<(std::ostream& os, std::queue<T, Container> q);

template <class T, class Container, class Comp>
std::ostream& operator<<(std::ostream& os,
                         std::priority_queue<T, Container, Comp> pq);

template <class T, class Container>
std::ostream& operator<<(std::ostream& os, std::stack<T, Container> st);

template <class T, class U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p);

template <class... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& t);

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

}  // namespace internal

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

template <std::ranges::range Range>
requires(!std::is_convertible_v<Range, std::string>)
std::ostream& operator<<(std::ostream& os, const Range& r) {
  if (r.empty()) return os;

  char delimiter = ' ';
  for (const auto& x : r) {
    using T = std::decay_t<decltype(x)>;
    if (internal::delimiter_of<T>()(x) == '\n') {
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
std::ostream& operator<<(std::ostream& os, std::queue<T, Container> q) {
  std::vector<T> v(q.size());
  int i = 0;
  while (!q.empty()) {
    v[i++] = q.front();
    q.pop();
  }
  return os << v;
}

template <class T, class Container, class Comp>
std::ostream& operator<<(std::ostream& os,
                         std::priority_queue<T, Container, Comp> pq) {
  std::vector<T> v(pq.size());
  int i = 0;
  while (!pq.empty()) {
    v[i++] = pq.top();
    pq.pop();
  }
  return os << v;
}

template <class T, class Container>
std::ostream& operator<<(std::ostream& os, std::stack<T, Container> st) {
  std::vector<T> v(st.size());
  int i = 0;
  while (!st.empty()) {
    v[i++] = st.top();
    st.pop();
  }
  return os << v;
}

template <class T, class U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
  return os << std::tie(p.first, p.second);
}

template <class... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& t) {
  constexpr size_t n = sizeof...(Args);
  if (n == 0) return os;

  char delimiter = ' ';
  [&]<size_t... I>(std::index_sequence<I...>) {
    (
        [&](const auto& x) {
          using T = std::decay_t<decltype(x)>;
          if (internal::delimiter_of<T>()(x) == '\n') {
            delimiter = '\n';
          }
        }(std::get<I>(t)),
        ...);
  }(std::make_index_sequence<n>());

  std::apply(
      [&](const auto&... args) {
        bool first = true;
        ((first ? (os << args) : (os << delimiter << args), first = false),
         ...);
      },
      t);

  return os;
}

}  // namespace cp