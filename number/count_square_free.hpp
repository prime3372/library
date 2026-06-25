#pragma once

#include <cassert>
#include <vector>
#include "isqrt.hpp"
#include "mobius.hpp"

// https://smsxgz.github.io/post/pe/counting_square_free_numbers/
long long count_square_free(long long n) {
  assert(0 <= n);
  long long ans = 0;
  int Imax = int(kth_root(n, 5)), D = int(isqrt(n / Imax));
  std::vector<int> mu = mobius(D), M(D + 1);

  for (int i = 1; i <= D; i++) {
    ans += mu[i] * (n / i / i);
    M[i] = M[i - 1] + mu[i];
  }

  long long Mxi_sum = 0;
  std::vector<long long> Mx(Imax);
  for (int i = Imax - 1; i >= 1; i--) {
    long long xi = isqrt(n / i), r = isqrt(xi), Mxi = 1;

    for (int j = 1; j <= xi / (r + 1); j++) {
      Mxi -= (xi / j - xi / (j + 1)) * M[j];
    }

    for (int j = 2; j <= r; j++) {
      if (xi / j <= D) Mxi -= M[xi / j];
      else Mxi -= Mx[j * j * i];
    }

    Mxi_sum += Mxi;
    Mx[i] = Mxi;
  }

  ans += Mxi_sum - 1LL * (Imax - 1) * M[D];
  return ans;
}
