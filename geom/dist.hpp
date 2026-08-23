#pragma once

#include "geom/intersect.hpp"
#include "geom/point.hpp"
#include "geom/projection.hpp"
#include "geom/segment.hpp"

namespace cp {

template <class T> long double dist(const point<T>& p, const point<T>& q) {
  return abs(p - q);
}

template <class T> long double dist(const point<T>& p, const line<T>& l) {
  return std::abs(cross(p - l.p, l.q - l.p)) / abs(l.q - l.p);
}

template <class T> long double dist(const point<T>& p, const segment<T>& l) {
  point<T> h = projection(p, l);
  if (is_on(h, l)) return dist(h, p);
  return std::min(dist(l.p, p), dist(l.q, p));
}

template <class T> long double dist(const segment<T>& l, const segment<T>& m) {
  if (intersect(l, m)) return 0;
  return std::min({dist(l.p, m), dist(l.q, m), dist(m.p, l), dist(m.q, l)});
}

}  // namespace cp