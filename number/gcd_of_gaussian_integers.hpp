#pragma once

#include "number/gaussian_integer.hpp"

namespace cp {

gaussian_integer gcd(const gaussian_integer& z1, const gaussian_integer& z2) {
  if (z2 == gaussian_integer{0, 0}) return z1;
  return gcd(z2, z1 % z2);
}

} // namespace cp