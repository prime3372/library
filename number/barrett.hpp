#pragma once

// Barrett reduction
struct barrett {
public:
  explicit constexpr barrett(unsigned int _m) : m(_m), im((unsigned long long)(-1) / _m + 1) {}

  constexpr unsigned int umod() const { return m; }

  // @param a, b (0 <= a < m, 0 <= b < m)
  // @return a * b % m
  constexpr unsigned int mul(unsigned int a, unsigned int b) const {
    // im = ceil(2^64 / m)
    // -> im * m = 2^64 + r (0 <= r < m)
    // let z = a*b = c*m + d (0 <= c, d < m)
    // a*b * im = (c*m + d) * im = c*(im*m) + d*im = c*2^64 + c*r + d*im
    // c*r + d*im < m*m + m*im < m*m + 2^64 + m = 2^64 + m*(m + 1) < 2^64 * 2
    // (a*b * im) >> 64 = c or c + 1

    unsigned long long z = a;
    z *= b;
    unsigned long long x = (unsigned long long)(((unsigned __int128)(z) * im) >> 64);
    unsigned long long y = x * m; // y = c*m or c*m + m
    return (unsigned int)(z - y + (z < y ? m : 0)); // d = a*b - c*m
  }

private:
  unsigned int m;
  unsigned long long im;
};
