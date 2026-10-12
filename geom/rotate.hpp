#pragma once

#include <cmath>

#include "geom/point.hpp"
#include "util/type-traits.hpp"

namespace cp {

template <class T>
Point<long double> rotate(const Point<T>& p, long double rad) {
  long double theta = arg(p) + rad;
  return abs(p) * Point<long double>(std::cos(theta), std::sin(theta));
}

}  // namespace cp