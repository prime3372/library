#pragma once

#include <algorithm>

#include "poly/convolution.hpp"
#include "poly/formal_power_series.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> inv(const formal_power_series<mint>& f, int n) {
  assert(!f.empty() && f[0] != 0);
  formal_power_series<mint> g = {f[0].inv()};
  g.reserve(n);
  for (int k = 1; k < n; k *= 2) {
    auto f2 = f.prefix(2 * k);
    auto g2 = g.prefix(2 * k);
    internal::ntt(f2);
    internal::ntt(g2);
    for (int i = 0; i < 2 * k; i++) f2[i] *= g2[i];
    internal::intt(f2);
    // Although the values of the lower k-1 terms are corrupted by cyclic
    // convolution, padding them with zeros yields g_k * f - 1 (mod x^{2*k})
    // because the definition of g_k implies that g_k * f = 1 (mod x^k).
    for (int i = 0; i < k - 1; i++) f2[i] = 0;
    internal::ntt(f2);
    for (int i = 0; i < 2 * k; i++) f2[i] *= g2[i];
    internal::intt(f2);
    for (int i = k; i < std::min(n, 2 * k); i++) g.emplace_back(-f2[i]);
  }
  return g;
}

template <class mint>
formal_power_series<mint> inv(const formal_power_series<mint>& f) {
  return inv(f, int(f.size()));
}

}  // namespace cp