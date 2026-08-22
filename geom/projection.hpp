#pragma once

#include "geom/line.hpp"
#include "geom/point.hpp"

namespace cp {

point projection(const point& p, const line& l) {
  return l.p + (l.q - l.p) * dot(l.q - l.p, p - l.p) / norm(l.q - l.p);
}

}  // namespace cp