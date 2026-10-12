#pragma once

#include "geom/line.hpp"
#include "geom/point.hpp"

namespace cp {

Point<long double> projection(const Point<long double>& p,
                              const Line<long double>& l) {
  return l.p + (l.q - l.p) * dot(l.q - l.p, p - l.p) / norm(l.q - l.p);
}

template <class T, class U>
Point<long double> projection(const Point<T>& p, const Line<U>& l) {
  return projection(Point<long double>(p), Line<long double>(l));
}

}  // namespace cp