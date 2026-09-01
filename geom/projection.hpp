#pragma once

#include "geom/line.hpp"
#include "geom/point.hpp"

namespace cp {

point<long double> projection(const point<long double>& p,
                              const line<long double>& l) {
  return l.p + (l.q - l.p) * dot(l.q - l.p, p - l.p) / norm(l.q - l.p);
}

template <class T, class U>
point<long double> projection(const point<T>& p, const line<U>& l) {
  return projection(point<long double>(p), line<long double>(l));
}

}  // namespace cp