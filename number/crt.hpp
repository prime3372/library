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
    
    if (m0 % m1 == 0) {
      if (r0 % m1 != r1) return {0, 0};
      continue;
    }

    auto [g, im] = ext_gcd(m0, m1);
    if ((r1 - r0) % g) return {0, 0};

    long long u1 = m1 / g;
    long long x = (r1 - r0) / g % u1 * im % u1;
    if (x < 0) x += u1;
    r0 += x * m0;
    m0 *= u1;
  }
  return {r0, m0};
}
