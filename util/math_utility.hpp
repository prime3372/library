#pragma once

namespace cp {

inline __int128 ipow(__int128 x, __int128 n) {
  __int128 r = 1;
  while (n) {
    if (n & 1) r *= x;
    x *= x;
    n >>= 1;
  }
  return r;
}

template <class T> inline bool chmin(T& a, T b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}

template <class T> inline bool chmax(T& a, T b) {
  if (b > a) {
    a = b;
    return true;
  }
  return false;
}

} // namespace cp