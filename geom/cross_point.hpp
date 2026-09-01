#pragma once

#include "geom/line.hpp"
#include "geom/point.hpp"

namespace cp {

point<long double> cross_point(const line<long double>& l,
                               const line<long double>& m) {
  long double a = cross(l.q - l.p, m.q - m.p);
  long double b = cross(l.q - l.p, l.q - m.p);
  if (internal::equal(a, 0.0L) && internal::equal(b, 0.0L)) return m.p;
  return m.p + (m.q - m.p) * b / a;
}

template <class T, class U>
point<long double> cross_point(const line<T>& l, const line<U>& m) {
  return cross_point(line<long double>(l), line<long double>(m));
}

}  // namespace cp