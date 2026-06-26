#pragma once

#include <cassert>
#include <utility>
#include <vector>
#include "ext_gcd.hpp"

std::pair<long long, long long> crt(const std::vector<long long>& r, const std::vector<long long>& m) {
  assert(r.size() == m.size());
  int n = int(r.size());
  long long r0 = 0, m0 = 1;
  for (int i = 0; i < n; ++i) {
    assert(1 <= m[i]);
    long long r1 = r[i] % m[i], m1 = m[i];
    if (r1 < 0) r1 += m1;
    if (m0 < m1) {
      std::swap(r0, r1);
      std::swap(m0, m1);
    }
    // we want to find (m, r) s.t. z % m0 = r0 and z % m1 = r1 <=> z % m = r (0 <= r < m)
    // let (x, y) satisfies z = m0*x + r0 = m1*y + r1 ...[1]

    if (m0 % m1 == 0) { // by[1]: m0 = 0 (mod m1) -> r0 = r1 (mod m1)
      if (r0 % m1 != r1) return {0, 0};
      continue; // m = m0, r = r0
    }

    auto [g, im] = ext_gcd(m0, m1);
    if ((r1 - r0) % g) return {0, 0};
    // by[1]: m0*x + r0 = m1*y + r1
    //        -> m0*x - m1*y = r1 - r0
    //        -> (r1 - r0) % g = 0

    long long u1 = m1 / g;
    long long x0 = (r1 - r0) / g % u1 * im % u1;
    if (x0 < 0) x0 += u1;
    // m0*x + r0 = r1 (mod m1)
    // -> (m0/g)*x = (r1 - r0)/g (mod u1)
    // -> x = (r1 - r0)/g*im (mod u1)
    // so let x0 = (r1 - r0)/g*im % u1

    // z = m0*(x0 + u1*k) + r0 = m0*x0 + r0 + m0*u1*k
    // -> z % (m0*u1) = m0*x0 + r0
    // note that:
    // 0 <= x0 < u1, 0 <= r0 < m0
    // -> 0 <= m0*x0 + r0 < m0*(u1 - 1) + m0 = m0*u1

    // now suppose z % (m0*u1) = m0*x0 + r0, then
    // z % m0 = r0
    // z % m1 = (m0*x + r0) % m1 = (m1*y + r1) % m1 = r1
    // therefore m = m0*u1, r = m0*x0 + r0

    r0 += x0 * m0;
    m0 *= u1;
  }
  return {r0, m0};
}
