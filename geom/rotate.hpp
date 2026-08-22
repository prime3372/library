#pragma once

#include <cmath>

#include "geom/point.hpp"

namespace cp {

point rotate(const point& p, long double rad) {
  long double theta = arg(p) + rad;
  return norm(p) * point(std::cos(theta), std::sin(theta));
}

}  // namespace cp