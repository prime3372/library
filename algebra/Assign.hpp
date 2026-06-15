#pragma once

template <class T> struct Assign {
  struct S = {
    T val;
    bool id;
    S() : val(), id(true) {}
    S(T v) : val(v), id(false) {}
  };
  static op(S x, S y) { return y.id ? x : y; }
  static e() { return S(); }
  Assign() = delete;
}
