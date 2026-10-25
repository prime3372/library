#pragma once

#include "geom/point.hpp"
#include "geom/projection.hpp"
#include "util/type-traits.hpp"

namespace cp {

template <class T>
  requires(internal::is_floating_point_v<T>)
Point<T> reflection(const Point<T>& p, const Line<T>& l) {
  return 2 * projection(p, l) - p;
}

}  // namespace cp