#pragma once

#include "geom/intersect.hpp"
#include "geom/point.hpp"
#include "geom/projection.hpp"
#include "geom/segment.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T> long double dist(const point<T>& p, const point<T>& q) {
  return abs(p - q);
}
template <class T> requires internal::is_integral_v<T>
long double dist(const point<T>& p, const point<T>& q) {
  return dist(point<long double>(p), point<long double>(q));
}

template <class T> long double dist(const point<T>& p, const line<T>& l) {
  return std::abs(cross(p - l.p, l.q - l.p)) / abs(l.q - l.p);
}
template <class T> requires internal::is_integral_v<T>
long double dist(const point<T>& p, const line<T>& l) {
  return dist(point<long double>(p), line<long double>(l));
}

template <class T> long double dist(const point<T>& p, const segment<T>& l) {
  auto h = projection(p, l);
  if (is_on(h, l)) return dist(h, p);
  return std::min(dist(l.p, p), dist(l.q, p));
}
template <class T> requires internal::is_integral_v<T>
long double dist(const point<T>& p, const segment<T>& l) {
  return dist(point<long double>(p), segment<long double>(l));
}

template <class T> long double dist(const segment<T>& l, const segment<T>& m) {
  if (intersect(l, m)) return 0;
  return std::min({dist(l.p, m), dist(l.q, m), dist(m.p, l), dist(m.q, l)});
}
template <class T> requires internal::is_integral_v<T>
long double dist(const segment<T>& l, const segment<T>& m) {
  return dist(segment<long double>(l), segment<long double>(m));
}

}  // namespace cp