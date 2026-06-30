#pragma once

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
      unsigned __int128 zl = (unsigned long long)(z);

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
