#pragma once

#include "geom/line.hpp"
#include "geom/point.hpp"

namespace cp {

Point<long double> cross_point(const Line<long double>& l,
                               const Line<long double>& m) {
  long double a = cross(l.q - l.p, m.q - m.p);
  long double b = cross(l.q - l.p, l.q - m.p);
  if (internal::equal(a, 0.0L) && internal::equal(b, 0.0L)) return m.p;
  return m.p + (m.q - m.p) * b / a;
}

template <class T, class U>
Point<long double> cross_point(const Line<T>& l, const Line<U>& m) {
  return cross_point(Line<long double>(l), Line<long double>(m));
}

}  // namespace cp