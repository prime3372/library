#pragma once

#include <algorithm>
#include <bit>
#include <vector>

#include "number/ext_gcd.hpp"
#include "number/pow_mod.hpp"
#include "util/static_modint.hpp"
#include "util/type_traits.hpp"

namespace cp {

namespace internal {

constexpr int primitive_root_ntt(int m) {
  if (m == 2) return 1;
  if (m == 998244353) return 3;
  if (m == 2113929217) return 5;
  if (m == 2130706433) return 3;
  int divs[20] = {};
  divs[0] = 2;
  int cnt = 1;
  int x = (m - 1) / 2;
  while (x % 2 == 0) x /= 2;
  for (int i = 3; 1LL * i * i <= x; i += 2) {
    if (x % i == 0) {
      divs[cnt++] = i;
      while (x % i == 0) x /= i;
    }
  }
  if (x > 1) divs[cnt++] = x;
  for (int g = 2;; g++) {
    bool ok = true;
    for (int i = 0; i < cnt; i++) {
      if (pow_mod(g, (m - 1) / divs[i], m) == 1) {
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

  // example: n = 8
  // start a = [0] [4] [2] [6] [1] [5] [3] [7]
  // step1 a = [0   4] [2   6] [1   5] [3   7]
  // step2 a = [0   2   4   6] [1   3   5   7]
  // step3 a = [0   1   2   3   4   5   6   7]
  // where [i_0 ... i_k] denotes NTT of a[i_0,...,i_k]

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

template <class mint>
std::vector<mint> convolution_naive(const std::vector<mint>& a,
                                    const std::vector<mint>& b) {
  int n = int(a.size()), m = int(b.size());
  std::vector<mint> ans(n + m - 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ans[i + j] += a[i] * b[j];
    }
  }
  return ans;
}

}  // namespace internal

template <class mint> requires internal::is_static_modint_v<mint>
std::vector<mint> convolution(std::vector<mint> a, std::vector<mint> b) {
  static constexpr int g = internal::primitive_root_ntt(mint::mod());
  static constexpr int ig = inv_mod(g, mint::mod());

  int n = int(a.size()), m = int(b.size());
  if (n == 0 || m == 0) return {};

  int z = int(std::bit_ceil((unsigned int)(n + m - 1)));
  assert((mint::mod() - 1) % z == 0);

  if (std::min(n, m) <= 60) {
    return internal::convolution_naive(std::move(a), std::move(b));
  }

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

template <int mod = 998244353, class T, class U = T>
requires internal::is_integral_v<T> && internal::is_integral_v<U>
std::vector<U> convolution(std::vector<T> a, std::vector<T> b) {
  using mint = static_modint<mod>;
  int n = int(a.size()), m = int(b.size());

  std::vector<mint> a2(n), b2(m);
  for (int i = 0; i < n; i++) a2[i] = mint(a[i]);
  for (int i = 0; i < m; i++) b2[i] = mint(b[i]);

  auto c2 = convolution(std::move(a2), std::move(b2));
  std::vector<U> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) c[i] = c2[i].val();
  return c;
}

}  // namespace cp