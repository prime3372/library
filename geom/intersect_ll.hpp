#pragma once

#include "geom/intersect_pl.hpp"
#include "geom/line.hpp"

namespace cp {

template <class T> bool intersect(const line<T>& l, const line<T>& m) {
  return !is_parallel(l, m) || intersect(l.p, m);
}

}  // namespace cp