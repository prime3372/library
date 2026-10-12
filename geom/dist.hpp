#pragma once

#include "geom/intersect.hpp"
#include "geom/point.hpp"
#include "geom/projection.hpp"
#include "geom/segment.hpp"

namespace cp {

// point-line

long double dist(const Point<long double>& p, const Line<long double>& l) {
  return std::abs(cross(p - l.p, l.q - l.p)) / abs(l.q - l.p);
}

template <class T, class U>
long double dist(const Point<T>& p, const Line<U>& l) {
  return dist(Point<long double>(p), Line<long double>(l));
}

// point-segment

long double dist(const Point<long double>& p, const Segment<long double>& s) {
  Point<long double> h = projection(p, Line<long double>(s));
  if (on(h, s)) return abs(h - p);
  return std::min(abs(s.p - p), abs(s.q - p));
}

template <class T, class U>
long double dist(const Point<T>& p, const Segment<U>& s) {
  return dist(Point<long double>(p), Segment<long double>(s));
}

// line-segment

long double dist(const Line<long double>& l, const Segment<long double>& s) {
  if (intersect(l, s)) return 0;
  return std::min(dist(s.p, l), dist(s.q, l));
}

template <class T, class U>
long double dist(const Line<T>& l, const Segment<U>& s) {
  return dist(Line<long double>(l), Segment<long double>(s));
}

// segment-segment

long double dist(const Segment<long double>& s, const Segment<long double>& t) {
  if (intersect(s, t)) return 0;
  return std::min({dist(s.p, t), dist(s.q, t), dist(t.p, s), dist(t.q, s)});
}

template <class T, class U>
long double dist(const Segment<T> s, const Segment<U>& t) {
  return dist(Segment<long double>(s), Segment<long double>(t));
}

}  // namespace cp