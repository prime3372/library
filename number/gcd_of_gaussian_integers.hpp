#pragma once

#include "number/gaussian_integer.hpp"

namespace cp {

gaussian_integer gcd(const gaussian_integer& z1, const gaussian_integer& z2) {
  return (z2.x == 0 && z2.y == 0) ? z1 : gcd(z2, z1 % z2);
}

}  // namespace cp