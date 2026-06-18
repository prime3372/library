#pragma once

// Barett reduction
struct barrett {
public:
  explicit barrett(unsigned int _m) : m(_m), im((unsigned long long)(-1) / _m + 1) {}

  unsigned int umod() const { return m; }

  unsigned int mul(unsigned int a, unsigned int b) const {
    unsigned long long z = a;
    z *= b;
    unsigned long long x = (unsigned long long)(((unsigned __int128)(z) * im) >> 64);
    unsigned long long y = x * m;
    return (unsigned int)(z - y + (z < y ? m : 0));
  }

private:
  unsigned int m;
  unsigned long long im;
};
