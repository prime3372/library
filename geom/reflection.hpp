#pragma once

#include "geom/point.hpp"
#include "geom/projection.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T> point<T> reflection(const point<T>& p, const line<T>& l) {
  return 2 * projection(p, l) - p;
}

template <class T> requires internal::is_integral_v<T>
point<long double> reflection(const point<T>& p, const line<T>& l) {
  return 2 * projection(point<long double>(p), line<long double>(l));
}

}  // namespace cp