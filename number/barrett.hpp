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

// Barrett reduction (64bit)
struct barrett64 {
public:
  explicit constexpr barrett64(unsigned long long _m) : m(_m) {
    unsigned __int128 im = (unsigned __int128)(-1) / _m + 1;
    ih = im >> 64;
    il = (im << 64) >> 64;
    ih_il = ih + il;
  }

  constexpr unsigned long long umod() { return m; }

  constexpr unsigned long long mul(unsigned long long a, unsigned long long b) {
    unsigned __int128 z = a;
    z *= b;

    unsigned __int128 x;
    {
      unsigned __int128 zh = z >> 64;
      unsigned __int128 zl = (z << 64) >> 64;

      unsigned __int128 high = zh * ih;
      unsigned __int128 low = zl * il;
      unsigned __int128 mid = (zh + zl) * ih_il - high - low;
      // (zh + zl) * (ih + il) - high - low = zh*il + zl*ih
      // zh*il + zl*ih < 2^128, because...
      // im = ceil(2^128 / m) = floor((2^128 + m - 1) / m)
      // -> ih = floor(im / 2^64)
      //       = floor((2^128 + m - 1) / m2^64) (note that floor(floor(a/b)/c) = floor(a/bc))
      //       = floor(2^64/m + (m-1)/m2^64)
      // let 2^64/m = q + r/m, then
      // ih = floor(q + r/m + (m-1)/m2^64)
      // -> r/m + (m-1)/m2^64 <= (m-1)/m + (m-1)/m2^64
      //                      < (m-1)/m + (m-1)/m^2
      //                      = (m+1)(m-1)/m^2
      //                      < 1
      // -> floor(q + r/m + (m-1)/m2^64) = q,
      // -> ih = floor(2^64 / m) <= 2^64 / m ...[1]
      // zh = floor(z / 2^64) <= (m-1)^2 / 2^64 ...[2]
      // by [1][2]: zh + ih <= 2^64/m + (m-1)^2/2^64
      //                    < 2^64/m + (m-1)2^64/m
      //                    = 2^64 ...[3]
      // by [3]:
      // zh*il + zl*ih <= zh*(2^64-1) + (2^64-1)*zl = (zh + zl)(2^64 - 1) < 2^64(2^64 - 1) < 2^128

      x = high + (mid >> 64) + (((low >> 64) + (unsigned long long)(mid)) >> 64);
    }
    unsigned __int128 y = x * m;
    return (unsigned long long)(z - y + (z < y ? m : 0));
  }

private:
  unsigned long long m, ih, il, ih_il;
};
