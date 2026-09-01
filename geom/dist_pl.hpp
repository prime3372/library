#pragma once

#include "geom/point.hpp"
#include "geom/line.hpp"

namespace cp {

long double dist(const point<long double>& p, const line<long double>& l) {
  return std::abs(cross(p - l.p, l.q - l.p)) / abs(l.q - l.p);
}

template <class T, class U>
long double dist(const point<T>& p, const line<U>& l) {
  return dist(point<long double>(p), line<long double>(l));
}

} // namespace cp