#pragma once

#include <algorithm>
#include <type_traits>

template <class T> struct Assign {
  struct S {
    T val;
    bool id;
    S() : val(), id(true) {}
    S(T v) : val(v), id(false) {}
  };
  static S op(S f, S g) { return g.id ? f : g; }
  static S e() { return S(); }
  
  Assign() = delete;
};
