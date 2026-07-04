#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace cp {

template <class T> size_t hash_combine(size_t seed, const T& val) {
  return seed ^ (std::hash<T>()(val) + 0x9e3779b97f4a7c15 + (seed << 12) + (seed >> 4));
}

} // namespace cp

namespace std {

  template <class T, size_t n> struct hash<std::array<T, n>> {
    hash() {}
    size_t operator()(const array<T, n>& a) const {
      size_t hs = 0;
      for (auto& elem : a) hs = cp::hash_combine(hs, elem);
      return hs;
    }
  };

  template <class T, class U> struct hash<pair<T, U>> {
    hash() {}
    size_t operator()(const std::pair<T, U>& p) const {
      return cp::hash_combine(cp::hash_combine(0, p.first), p.second);
    }
  };

  template <> struct hash<string> {
    hash() {}
    size_t operator()(const string& s) const {
      size_t hs = 0;
      for (auto& c : s) hs = cp::hash_combine(hs, c);
      return hs;
    }
  };

  template <class... Args> struct hash<tuple<Args...>> {
    hash() {}
    size_t operator()(const std::tuple<Args...> t) const {
      return std::apply([](const auto&... args) { return combine(0, args...); }, t);
    }
  private:
    template <class Head, class... Tail>
    static size_t combine(size_t hs, Head&& head, Tail&&... tail) {
      return combine(cp::hash_combine(hs, head), std::forward<Tail>(tail)...);
    }
    static size_t combine(size_t hs) { return hs; }
  };

  template <class T> struct hash<std::vector<T>> {
    hash() {}
    size_t operator()(const vector<T>& v) const {
      size_t hs = 0;
      for (auto& elem : v) hs = cp::hash_combine(hs, elem);
      return hs;
    }
  };

} // namespace std