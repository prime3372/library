#pragma once

#include "geom/line.hpp"
#include "geom/point.hpp"
#include "util/type-traits.hpp"

namespace cp {

template <class T>
  requires(internal::is_floating_point_v<T>)
Point<T> projection(const Point<T>& p, const Line<T>& l) {
  return l.p + (l.q - l.p) * dot(l.q - l.p, p - l.p) / norm(l.q - l.p);
}

}  // namespace cp