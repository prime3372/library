#pragma once

#include <cmath>

#include "geom/point.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T>
point<long double> rotate(const point<T>& p, long double rad) {
  long double theta = arg(p) + rad;
  return abs(p) * point<long double>(std::cos(theta), std::sin(theta));
}

}  // namespace cp