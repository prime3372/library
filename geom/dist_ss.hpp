#pragma once

#include "geom/dist_ps.hpp"
#include "geom/intersect_ss.hpp"
#include "geom/point.hpp"
#include "geom/segment.hpp"

namespace cp {

long double dist(const segment<long double>& s, const segment<long double>& t) {
  if (intersect(s, t)) return 0;
  return std::min({dist(s.p, t), dist(s.q, t), dist(t.p, s), dist(t.q, s)});
}

template <class T, class U>
long double dist(const segment<T> s, const segment<U>& t) {
  return dist(segment<long double>(s), segment<long double>(t));
}

}  // namespace cp