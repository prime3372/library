#pragma once

#include "geom/intersect.hpp"
#include "geom/point.hpp"
#include "geom/projection.hpp"
#include "geom/segment.hpp"

namespace cp {

long double dist(const point& p, const point& q) { return abs(p - q); }

long double dist(const point& p, const line& l) {
  return std::abs(cross(p - l.p, l.q - l.p)) / abs(l.q - l.p);
}

long double dist(const point& p, const segment& l) {
  point h = projection(p, l);
  if (is_on(h, l)) return dist(h, p);
  return std::min(dist(l.p, p), dist(l.q, p));
}

long double dist(const segment& l, const segment& m) {
  if (intersect(l, m)) return 0;
  return std::min({dist(l.p, m), dist(l.q, m), dist(m.p, l), dist(m.q, l)});
}

}  // namespace cp