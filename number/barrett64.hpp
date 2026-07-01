#pragma once

#include <bit>

// Barrett Reduction (64bit)
struct barrett64 {
public:
  explicit constexpr barrett64(unsigned long long _m) : m(_m) {
    w = std::bit_width(m);
    im = (((unsigned __int128)(1) << (63 + w)) - 1) / _m + 1;
    // im = ceil(2^(63+w) / m)
    //    = floor((2^(63+w) - 1) / m) + 1
    //    = floor(2^(63+w)/m - 1/m) + 1
    //    <= 2^(63+w)/m - 1/m + 1
    //    <= 2^(63+w)/2^(w-1) - 1/m + 1
    //    = 2^64 + 1 - 1/m
    //    <= 2^64
  }

  constexpr unsigned long long umod() const { return m; }

  constexpr unsigned long long mul(unsigned long long a, unsigned long long b) const {
    unsigned __int128 z = a;
    z *= b;
    unsigned __int128 x = ((z >> w) * im) >> 63;
    // a * b < 2^(2w)
    // a * b / 2^w < 2^w
    // [a * b / 2^w] < 2^w
    // [z / 2^w] < 2^w < 2^64
    // [z / 2^w] * im < 2^128

    // im = ceil(2^(63+w) / m)
    // im*m = 2^(63+w) + r (0 <= r < m)
    // z = a*b = c*m + d (0 <= c, d < m)

    // x = [[z / 2^w]*im / 2^63]
    //   <= z * im / 2^(63+w)
    //   = (c*m + d)*im / 2^(63+w)
    //   = (c*m*im + d*im) / 2^(63+w)
    //   = (c2^(63+w) + c*r + d*im) / 2^(63+w)
    //   = c + (c*r + d*im) / 2^(63+w)
    //   < c + (m^2 + m*im) / 2^(63+w)
    //   <= c + (m^2 + 2^(63+w) + r) / 2^(63+w)
    //   = c + 1 + (m^2 + r) / 2^(63+w)
    //   < c + 1 + (m^2 + m) / 2^(63+w)
    //   = c + 1 + m(m + 1) / 2^(63+w)
    //   < c + 1 + 2^(2w) / 2^(63+w)
    //   = c + 1 + 2^w / 2^63
    //   <= c + 3

    // x = [[z / 2^w]*im / 2^63]
    //   = [ceil((z - 2^w + 1) / 2^w) * im / 2^63]
    //   >= [(z - 2^w + 1) * im / 2^(63+w)]
    //   = [(c*m + d - 2^w + 1) * im / 2^(63+w)]
    //   = [(c*m*im + d*im - (2^w-1)*im) / 2^(63+w)]
    //   >= [(c*m*im + d*im - m*im) / 2^(63+w)]
    //   = [((c-1)*m*im + d*im) / 2^(63+w)]
    //   >= [((c-1)*(2^(63+w)+r) + d*im) / 2^(63+w)]
    //   = [c - 1 + ((c-1)*r + d*im) / 2^(63+w)]
    //   >= c - 2

    unsigned __int128 y = x * m;
    while (z < y) y -= m;
    while (y + m <= z) y += m; // y + m <= c*m + m <= (c+1)*m < (m+1)*m <= 2^2w <= 2^128
    return z - y;
  }

private:
  unsigned long long m;
  unsigned __int128 im;
  int w;
};
