#pragma once

#include <cassert>
#include <concepts>
#include <vector>

#include "poly/convolution.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T>
  requires (is_static_modint_v<T> && is_prime(T::mod()) || std::same_as<T, long long>)
struct formal_power_series {
private:
  using fps = formal_power_series;
  static constexpr bool is_mint = is_static_modint_v<T>;

public:
  formal_power_series() {}
  formal_power_series(int n) : f(n) {}
  formal_power_series(int n, T val) : f(n, val) {}
  formal_power_series(const std::vector<T>& v) : f(v) {}

  T& operator[](int i) {
    assert(0 <= i);
    if (i >= size()) resize(i + 1);
    return f[i];
  }
  const T& operator[](int i) const {
    assert(0 <= i && i < size());
    return f[i];
  };

  T& front() { return f.front(); }
  const T& front() const { return f.front(); }

  T& back() { return f.back(); }
  const T& back() const { return f.back(); }

  fps& operator+=(const fps& rhs) {
    if (rhs.size() > size()) f.resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] += rhs[i];
    return *this;
  }

  fps& operator-=(const fps& rhs) {
    if (rhs.size() > size()) f.resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] -= rhs[i];
    return *this;
  }

  fps& operator*=(const T& rhs) {
    for (int i = 0; i < size(); i++) f[i] *= rhs;
    return *this;
  }

  fps& operator*=(const fps& rhs) {
    f = convolution(f, rhs.f);
    return *this;
  }

  fps& operator/=(const T& rhs) {
    for (int i = 0; i < size(); i++) f[i] /= rhs;
    return *this;
  }

  fps operator+() const { return *this; }
  fps operator-() const { return fps() - *this; }

  T operator()(T x) const {
    T r = 0, w = 1;
    for (T& v : f) {
      r += w * v;
      w *= x;
    }
    return r;
  }

  friend fps operator+(const fps& lhs, const fps& rhs) { return fps(lhs) += rhs; }
  friend fps operator-(const fps& lhs, const fps& rhs) { return fps(lhs) -= rhs; }
  friend fps operator*(const fps& lhs, const T& rhs) { return fps(lhs) *= rhs; }
  friend fps operator*(const T& lhs, const fps& rhs) { return fps(rhs) *= lhs; }
  friend fps operator*(const fps& lhs, const fps& rhs) { return fps(lhs) *= rhs; }
  friend fps operator/(const fps& lhs, const T& rhs) { return fps(lhs) /= rhs; }
  friend fps operator/(const T& lhs, const fps& rhs) { return fps(rhs) /= lhs; }

  int size() const { return int(f.size()); }
  bool empty() { return f.empty(); }
  void resize(int n) { f.resize(n); }
  void shrink() { while (!empty() && back() == 0) f.pop_back(); }

  void swap(fps& other) { f.swap(other.f); }
  void clear() { f.clear(); }

private: 
  std::vector<T> f;
};

} // namespace cp