#pragma once

#include <algorithm>
#include <bit>
#include <vector>
#include "../number/is_prime.hpp"
#include "../number/pow_mod.hpp"
#include "../util/type_traits.hpp"

namespace internal {

constexpr int primitive_root_ntt(int p) {
  if (p == 2) return 1;
  if (p == 167772161) return 3;
  if (p == 469762049) return 3;
  if (p == 754974721) return 11;
  if (p == 998244353) return 3;
  std::vector<int> fs = {2};
  int x = p - 1;
  while (x % 2 == 0) x /= 2;
  for (int i = 3; 1LL * i * i <= x; i += 2) {
    if (x % i == 0) {
      fs.push_back(i);
      while (x % i == 0) x /= i;
    }
  }
  if (x > 1) fs.push_back(x);

  for (int g = 2;; g++) {
    bool ok = true;
    for (int f : fs) {
      if (pow_mod(g, (p - 1) / f, p) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return g;
  }
}

template <class mint, int g> std::vector<mint> ntt_root() {
  constexpr int rank2 = std::countr_zero((unsigned int)(mint::mod() - 1));
  std::vector<mint> root(rank2 + 1);
  root[rank2] = mint(g).pow((mint::mod() - 1) >> rank2);
  for (int i = rank2 - 1; i >= 0; i--) {
    root[i] = root[i + 1] * root[i + 1];
  }
  return root;
}

template <class mint, int g> void ntt(std::vector<mint>& a) {
  static auto root = ntt_root<mint, g>();
  int n = int(a.size());
  int log = int(std::countr_zero((unsigned int)(n)));

  std::vector<int> bitrev(n);
  for (int i = 0; i < n; i++) {
    bitrev[i] = (bitrev[i >> 1] >> 1) + ((i & 1) << (log - 1));
  }
  for (int i = 0; i < n; i++) {
    if (i < bitrev[i]) std::swap(a[i], a[bitrev[i]]);
  }

  for (int step = 1; step <= log; step++) {
    int width = 1 << step;
    int half = width / 2;
    for (int i = 0; i < n; i += width) {
      mint w = 1;
      for (int j = 0; j < half; j++) {
        mint l = a[i + j];
        mint r = a[i + j + half] * w;
        a[i + j] = l + r;
        a[i + j + half] = l - r;
        w *= root[step];
      }
    }
  }
}

} // namespace internal

template <class mint>
  requires is_static_modint_v<mint> && (is_prime(mint::mod()))
std::vector<mint> convolution(std::vector<mint> a, std::vector<mint> b) {
  static constexpr int g = internal::primitive_root_ntt(mint::mod());
  static constexpr int ig = pow_mod(g, mint::mod() - 2, mint::mod());

  int n = int(a.size()), m = int(b.size());
  if (n == 0 || m == 0) return {};

  int z = int(std::bit_ceil((unsigned int)(n + m - 1)));
  assert((mint::mod() - 1) % z == 0);

  a.resize(z);
  internal::ntt<mint, g>(a);
  b.resize(z);
  internal::ntt<mint, g>(b);

  for (int i = 0; i < z; i++) a[i] *= b[i];

  internal::ntt<mint, ig>(a);
  a.resize(n + m - 1);
  mint iz = mint(z).inv();
  for (int i = 0; i < n + m - 1; i++) a[i] *= iz;

  return a;
}
