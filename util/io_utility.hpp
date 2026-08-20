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
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "util/io_utility_base.hpp"

namespace cp {

template <class T, size_t Size>
std::istream& operator>>(std::istream& is, std::array<T, Size>& a);

template <class T, class U>
std::istream& operator>>(std::istream& is, std::pair<T, U>& p);

template <class... Args>
std::istream& operator>>(std::istream& is, std::tuple<Args...>& t);

template <class T, class Alloc>
std::istream& operator>>(std::istream& is, std::vector<T, Alloc>& v);

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

template <std::ranges::range Range>
requires(!std::is_convertible_v<Range, std::string>)
std::ostream& operator<<(std::ostream& os, const Range& r) {
  std::vector<std::string> outs;
  for (const auto& x : r) {
    std::ostringstream oss;
    oss << x;
    outs.push_back(oss.str());
  }
  return os << internal::combine_outputs(outs);
}

template <class T, class Container>
std::ostream& operator<<(std::ostream& os, std::queue<T, Container> q) {
  std::vector<T> v;
  v.reserve(q.size());
  while (!q.empty()) {
    v.push_back(q.front());
    q.pop();
  }
  return os << v;
}

template <class T, class Container, class Comp>
std::ostream& operator<<(std::ostream& os,
                         std::priority_queue<T, Container, Comp> pq) {
  std::vector<std::string> v;
  v.reserve(pq.size());
  while (!pq.empty()) {
    v.push_back(pq.top());
    pq.pop();
  }
  return os << v;
}

template <class T, class Container>
std::ostream& operator<<(std::ostream& os, std::stack<T, Container> st) {
  std::vector<T> v;
  v.reserve(st.size());
  while (!st.empty()) {
    v.push_back(st.top());
    st.pop();
  }
  return os << v;
}

template <class T, class U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
  return os << std::tie(p.first, p.second);
}

template <typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& t) {
  std::vector<std::string> outs;
  outs.reserve(sizeof...(Args));
  std::ostringstream oss;
  std::apply(
      [&](const auto&... args) {
        ((oss << args, outs.push_back(oss.str()), oss.str("")), ...);
      },
      t);
  return os << internal::combine_outputs(outs);
}

}  // namespace cp