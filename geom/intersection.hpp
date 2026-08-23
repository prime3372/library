#pragma once

#include "geom/line.hpp"
#include "geom/point.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T> point<T> intersection(const line<T>& l, const line<T>& m) {
  T a = cross(l.q - l.p, m.q - m.p);
  T b = cross(l.q - l.p, l.q - m.p);
  if (internal::equal(a, 0) && internal::equal(b, 0)) return m.p;
  return m.p + (m.q - m.p) * b / a;
}

template <class T> requires internal::is_integral_v<T>
point<long double> intersection(const line<T>& l, const line<T>& m) {
  return intersection(line<long double>(l), line<long double>(m));
}

}  // namespace cp