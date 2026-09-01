#pragma once

#include "geom/point.hpp"
#include "geom/projection.hpp"

namespace cp {

point<long double> reflection(const point<long double>& p,
                              const line<long double>& l) {
  return 2 * projection(p, l) - p;
}

template <class T, class U>
point<long double> reflection(const point<T>& p, const line<U>& l) {
  return reflection(point<long double>(p), line<long double>(l));
}

}  // namespace cp