#pragma once

#include "geom/line.hpp"

namespace cp {

template <class T> bool intersect(const line<T>& l, const line<T>& m) {
  return !is_parallel(l, m) || on(l.p, m);
}

}  // namespace cp