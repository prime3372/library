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
    // Suppose we have already computed g_k := g mod x**k. We want to find
    // g_{2*k} using Newton's method:
    // g_{2*k} = 2 * g_k - g_k * g_k * f mod x**{2*k}
    // Since g_k is already known, we only need to determine the upper
    // k terms of g_{2*k}.
    auto f2 = f.prefix(2 * k);
    auto g2 = g.prefix(2 * k);

    // By applying NTT and INTT to g_k and f, we obtain a cyclic convolution of
    // size 2*k. Although the values ​​of the lower k terms are corrupted,
    // the fact that g_k * f = 1 mod x**k means that padding the lower k terms
    // with zeros yields g_k * f - 1.
    internal::ntt(f2);
    internal::ntt(g2);
    for (int i = 0; i < 2 * k; i++) f2[i] *= g2[i];
    internal::intt(f2);
    for (int i = 0; i < k; i++) f2[i] = 0;

    // We then apply a cyclic convolution of size 2*k to g_k and g_k * f - 1.
    // Similarly, the lower k-1 terms become corrupted, but this poses no issue
    // since the target value consists of the upper k terms of g_{2*k}.
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