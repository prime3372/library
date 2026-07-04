#pragma once

#include <algorithm>
#include <bit>
#include <concepts>
#include <vector>

#include "number/ext_gcd.hpp"
#include "number/is_prime.hpp"
#include "number/pow_mod.hpp"
#include "util/type_traits.hpp"
#include "util/static_modint.hpp"

namespace cp {

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

template <int mod = 998244353, std::integral T>
std::vector<T> convolution(std::vector<T> a, std::vector<T> b) {
  using mint = static_modint<mod>;
  int n = int(a.size()), m = int(b.size());
  std::vector<mint> _a(n), _b(m);
  for (int i = 0; i < n; i++) _a[i] = mint(a[i]);
  for (int i = 0; i < m; i++) _b[i] = mint(b[i]);
  auto _c = convolution(std::move(_a), std::move(_b));
  std::vector<T> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) c[i] = _c[i].val();
  return c;
}

std::vector<long long> convolution(std::vector<long long> a, std::vector<long long> b) {
  int n = int(a.size()), m = int(b.size());
  if (n == 0 || m == 0) return {};
  assert(n + m - 1 <= (1 << 24));

  static constexpr long long MOD1 = 754974721;  // 45 * 2^24 + 1
  static constexpr long long MOD2 = 167772161;  //  5 * 2^25 + 1
  static constexpr long long MOD3 = 469762049;  //  7 * 2^26 + 1
  static constexpr __int128 MOD123 = __int128(MOD1) * MOD2 * MOD3;

  static constexpr long long i1 = inv_mod(MOD1, MOD2);
  static constexpr long long i2 = inv_mod(MOD1 * MOD2, MOD3);

  auto c1 = convolution<MOD1>(a, b);
  auto c2 = convolution<MOD2>(a, b);
  auto c3 = convolution<MOD3>(a, b);

  // restore the true value using CRT
  long long x;
  __int128 r;
  for (int i = 0; i < n + m - 1; i++) {
    x = (c2[i] - c1[i]) % MOD2 * i1 % MOD2;
    if (x < 0) x += MOD2;
    c1[i] += x * MOD1;

    x = (c3[i] - c1[i]) % MOD3 * i2 % MOD3;
    if (x < 0) x += MOD3;
    r = c1[i] + __int128(x) * MOD1 * MOD2;
    if (r > MOD123 / 2) r -= MOD123;
    c1[i] = (long long)(r);
  }
  return c1;
}

} // namespace cp