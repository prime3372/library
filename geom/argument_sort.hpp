#pragma once

#include <algorithm>
#include <vector>

#include "geom/point.hpp"

namespace cp {

// sort by atan2
// @note atan2(x < 0, y = 0) = pi and atan2(0, 0) = 0
void argument_sort(std::vector<ipoint>& ps) {
  std::sort(ps.begin(), ps.end(), [](const ipoint& p, const ipoint& q) {
    bool up_p = p.y > 0 || (p.y == 0 && p.x < 0);
    bool up_q = q.y > 0 || (q.y == 0 && q.x < 0);
    if (up_p != up_q) return !up_p && up_q;
    if (q.x == 0 && q.y == 0) return p.y < 0;
    return cross(p, q) > 0;
  });
}

}  // namespace cp