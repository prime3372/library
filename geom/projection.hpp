#pragma once

#include "geom/line.hpp"
#include "geom/point.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T> point<T> projection(const point<T>& p, const line<T>& l) {
  return l.p + (l.q - l.p) * dot(l.q - l.p, p - l.p) / norm(l.q - l.p);
}

template <class T> requires internal::is_integral_v<T>
point<long double> projection(const point<T>& p, const line<T>& l) {
  return projection(point<long double>(p), line<long double>(l));
}

}  // namespace cp