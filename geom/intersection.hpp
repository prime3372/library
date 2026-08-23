#pragma once

#include "geom/line.hpp"
#include "geom/point.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T> point<T> intersection(const line<T>& l, const line<T>& m) {
  point<T> a = m.p - l.p, b = m.q - l.p, c = l.q - l.p;
  return l.p + a + (b - a) * cross(c, a) / cross(c, a - b);
}

template <class T> requires internal::is_integral_v<T>
point<long double> intersection(const line<T>& l, const line<T>& m) {
  return intersection(line<long double>(l), line<long double>(m));
}

}  // namespace cp