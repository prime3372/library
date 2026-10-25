#pragma once

#include "geom/intersect.hpp"
#include "geom/point.hpp"
#include "geom/projection.hpp"
#include "geom/segment.hpp"
#include "util/type-traits.hpp"

namespace cp {

// point-line

template <class T>
  requires(internal::is_floating_point_v<T>)
T dist(const Point<T>& p, const Line<T>& l) {
  return std::abs(cross(p - l.p, l.q - l.p)) / abs(l.q - l.p);
}

// point-segment

template <class T>
  requires(internal::is_floating_point_v<T>)
T dist(const Point<T>& p, const Segment<T>& s) {
  Point<T> h = projection(p, Line<T>(s));
  if (on(h, s)) return abs(h - p);
  return std::min(abs(s.p - p), abs(s.q - p));
}

// line-segment

template <class T>
  requires(internal::is_floating_point_v<T>)
T dist(const Line<T>& l, const Segment<T>& s) {
  if (intersect(l, s)) return 0;
  return std::min(dist(s.p, l), dist(s.q, l));
}


// segment-segment

template <class T>
  requires(internal::is_floating_point_v<T>)
T dist(const Segment<T>& s, const Segment<T>& t) {
  if (intersect(s, t)) return 0;
  return std::min({dist(s.p, t), dist(s.q, t), dist(t.p, s), dist(t.q, s)});
}

}  // namespace cp