#pragma once

#include <algorithm>
#include <type_traits>

template <class T> struct Assign {
  struct F {
    T val;
    bool id;
    F() : val(), id(true) {}
    F(T v) : val(v), id(false) {}
  };
  static F composition(F g, F f) { return g.id ? f : g; }
  static F id() { return F(); }
  
  Assign() = delete;
};
