#pragma once

#include "geom/point.hpp"
#include "geom/projection.hpp"

namespace cp {

Point<long double> reflection(const Point<long double>& p,
                              const Line<long double>& l) {
  return 2 * projection(p, l) - p;
}

template <class T, class U>
Point<long double> reflection(const Point<T>& p, const Line<U>& l) {
  return reflection(Point<long double>(p), Line<long double>(l));
}

}  // namespace cp