#pragma once

#include "geom/point.hpp"
#include "geom/projection.hpp"
#include "geom/segment.hpp"

namespace cp {

long double dist(const point<long double>& p, const segment<long double>& s) {
  point<long double> h = projection(p, line<long double>(s));
  if (on(h, s)) return abs(h - p);
  return std::min(abs(s.p - p), abs(s.q - p));
}

template <class T, class U>
long double dist(const point<T>& p, const segment<U>& s) {
  return dist(point<long double>(p), segment<long double>(s));
}

}  // namespace cp