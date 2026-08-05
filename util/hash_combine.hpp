#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

template <class T> size_t hash_combine(size_t seed, const T& val) {
  return seed ^ (std::hash<T>()(val) + 0x9e3779b97f4a7c15 + (seed << 12) + (seed >> 4));
}

} // namespace cp

namespace std {

template <> struct hash<string> {
  hash() {}
  size_t operator()(const string& s) const {
    size_t hs = 0;
    for (auto& c : s) hs = cp::hash_combine(hs, c);
    return hs;
  }
};

template <class Tuple> requires cp::internal::is_tuple_like_v<Tuple>
struct hash<Tuple> {
public:
  hash() {}
  size_t operator()(const Tuple& t) const {
    return apply([](const auto&... args) {
      return combine(0, args...);
    }, t);
  }

private:
  template <class Head, class... Tail>
  static size_t combine(size_t hs, Head&& head, Tail&&... tail) {
    return combine(cp::hash_combine(hs, head), forward<Tail>(tail)...);
  }
  static size_t combine(size_t hs) { return hs; }
};

template <class T, class Alloc> struct hash<vector<T, Alloc>> {
  hash() {}
  size_t operator()(const vector<T, Alloc>& v) const {
    size_t hs = 0;
    for (auto& elem : v) hs = cp::hash_combine(hs, elem);
    return hs;
  }
};

} // namespace std