#pragma once

#include "geom/point.hpp"
#include "geom/projection.hpp"

namespace cp {

point reflection(const point& p, const line& l) {
  return 2 * projection(p, l) - p;
}

}  // namespace cp