#pragma once

#include "geom/line.hpp"
#include "geom/point.hpp"
#include "util/type-traits.hpp"

namespace cp {

template <class T>
  requires(internal::is_floating_point_v<T>)
Point<T> cross_point(const Line<T>& l, const Line<T>& m) {
  T a = cross(l.q - l.p, m.q - m.p);
  T b = cross(l.q - l.p, l.q - m.p);
  if (internal::equal(a, 0.0L) && internal::equal(b, 0.0L)) return m.p;
  return m.p + (m.q - m.p) * b / a;
}

}  // namespace cp