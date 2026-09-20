#pragma once

#include "geom/intersect.hpp"
#include "geom/point.hpp"
#include "geom/projection.hpp"
#include "geom/segment.hpp"

namespace cp {

// point-line

long double dist(const point<long double>& p, const line<long double>& l) {
  return std::abs(cross(p - l.p, l.q - l.p)) / abs(l.q - l.p);
}

template <class T, class U>
long double dist(const point<T>& p, const line<U>& l) {
  return dist(point<long double>(p), line<long double>(l));
}

// point-segment

long double dist(const point<long double>& p, const segment<long double>& s) {
  point<long double> h = projection(p, line<long double>(s));
  if (on(h, s)) return abs(h - p);
  return std::min(abs(s.p - p), abs(s.q - p));
}

template <class T, class U>
long double dist(const point<T>& p, const segment<U>& s) {
  return dist(point<long double>(p), segment<long double>(s));
}

// line-segment

long double dist(const line<long double>& l, const segment<long double>& s) {
  if (intersect(l, s)) return 0;
  return std::min(dist(s.p, l), dist(s.q, l));
}

template <class T, class U>
long double dist(const line<T>& l, const segment<U>& s) {
  return dist(line<long double>(l), segment<long double>(s));
}

// segment-segment

long double dist(const segment<long double>& s, const segment<long double>& t) {
  if (intersect(s, t)) return 0;
  return std::min({dist(s.p, t), dist(s.q, t), dist(t.p, s), dist(t.q, s)});
}

template <class T, class U>
long double dist(const segment<T> s, const segment<U>& t) {
  return dist(segment<long double>(s), segment<long double>(t));
}

}  // namespace cp