#pragma once

#include <algorithm>
#include <type_traits>

namespace cp {

template <class T, T lower> requires (std::is_arithmetic_v<T>)
struct max_assign {
  using S = T;
  static constexpr S op(S x, S y) { return std::max(x, y); }
  static constexpr S e() { return lower; }

  struct F {
    T val;
    bool id;
    F() : val(), id(true) {}
    F(T v) : val(v), id(false) {}
  }
  static constexpr S mapping(F f, S x) { return f.id ? x : f; }
  static constexpr F composition(F g, F f) { return g.id ? f : g; }
  static constexpr F id() { return F(); }
};

} // namespace cp