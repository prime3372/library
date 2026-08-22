#pragma once

#include "geom/line.hpp"
#include "geom/point.hpp"

namespace cp {

point intersection(const line& l, const line& m) {
  point a = m.p - l.p, b = m.q - l.p, c = l.q - l.p;
  return l.p + a + (b - a) * cross(c, a) / cross(c, a - b);
}

}  // namespace cp