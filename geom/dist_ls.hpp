#pragma once

#include "geom/dist_pl.hpp"
#include "geom/intersect_ls.hpp"
#include "geom/point.hpp"
#include "geom/segment.hpp"

namespace cp {

long double dist(const line<long double>& l, const segment<long double>& s) {
  if (intersect(l, s)) return 0;
  return std::min(dist(s.p, l), dist(s.q, l));
}

}  // namespace cp