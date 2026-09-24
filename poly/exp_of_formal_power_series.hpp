#pragma once

#include "poly/formal_power_series.hpp"
#include "poly/log_of_formal_power_series.hpp"

namespace cp {

template <class mint>
formal_power_series<mint> exp(const formal_power_series<mint>& f, int n) {
  assert(f.empty() || f[0] == 0);
  formal_power_series<mint> g = {1}, ig = {1};
  for (int k = 1; k < n; k *= 2) {
    auto z = g.prefix(2 * k);
    internal::ntt(z);
    auto iz = ig.prefix(2 * k);
    internal::ntt(iz);

    // compute precision-2k inv of precision-k g
    auto ig1 = z;
    for (int i = 0; i < 2 * k; i++) ig1[i] *= iz[i];
    internal::intt(ig1);
    for (int i = 0; i < k; i++) ig1[i] = 0;
    internal::ntt(ig1);
    for (int i = 0; i < 2 * k; i++) ig1[i] *= iz[i];
    internal::intt(ig1);
    for (int i = k; i < 2 * k; i++) ig.emplace_back(-ig1[i]);

    // compute precision-2k log of precision-k g
    auto log = integral(diff(g) * ig).prefix(2 * k);

    // compute precision-2k g
    auto h = log - f.prefix(2 * k);
    internal::ntt(h);
    for (int i = 0; i < 2 * k; i++) h[i] *= z[i];
    internal::intt(h);
    for (int i = k; i < std::min(2 * k, n); i++) g.emplace_back(-h[i]);

    // compute precision-2k inv of precision-2k g
    auto ig2 = g.prefix(2 * k);
    internal::ntt(ig2);
    for (int i = 0; i < 2 * k; i++) ig2[i] *= iz[i];
    internal::intt(ig2);
    for (int i = 0; i < k; i++) ig2[i] = 0;
    internal::ntt(ig2);
    for (int i = 0; i < 2 * k; i++) ig2[i] *= iz[i];
    internal::intt(ig2);
    ig.resize(k);
    for (int i = k; i < 2 * k; i++) ig.emplace_back(-ig2[i]);
  }
  return g.prefix(n);
}

template <class mint>
formal_power_series<mint> exp(const formal_power_series<mint>& f) {
  return exp(f, int(f.size()));
}

}  // namespace cp