#pragma once

#include <cassert>
#include <iostream>

namespace cp {

class ipoint {
 public:
  long long x, y;
  ipoint() : x(0), y(0) {}
  ipoint(long long _x, long long _y) : x(_x), y(_y) {}

  ipoint operator+() const { return *this; }
  ipoint operator-() const { return ipoint(-x, -y); }

  ipoint& operator+=(const ipoint& v) {
    x += v.x;
    y += v.y;
    return *this;
  }
  ipoint& operator-=(const ipoint& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  ipoint& operator*=(long long s) {
    x *= s;
    y *= s;
    return *this;
  }
  ipoint& operator/=(long long s) {
    x /= s;
    y /= s;
    return *this;
  }

  friend ipoint operator+(const ipoint& lhs, const ipoint& rhs) {
    return ipoint(lhs) += rhs;
  }
  friend ipoint operator-(const ipoint& lhs, const ipoint& rhs) {
    return ipoint(lhs) -= rhs;
  }
  friend ipoint operator*(const ipoint& lhs, long long rhs) {
    return ipoint(lhs) *= rhs;
  }
  friend ipoint operator*(long long lhs, const ipoint& rhs) {
    return ipoint(rhs) *= lhs;
  }
  friend ipoint operator/(const ipoint& lhs, long long rhs) {
    return ipoint(lhs) /= rhs;
  }

  long long norm2() const { return x * x + y * y; }

  ipoint rot() const { return ipoint(y, -x); }

  int ort() const {
    if (x == 0 && y == 0) return 0;
    if (x > 0 && y >= 0) return 1;
    if (x <= 0 && y > 0) return 2;
    if (x < 0 && y <= 0) return 3;
    return 4;
  }

  friend bool operator==(const ipoint& lhs, const ipoint& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
  friend bool operator!=(const ipoint& lhs, const ipoint& rhs) {
    return !(lhs == rhs);
  }
  friend bool operator<(const ipoint& lhs, const ipoint& rhs) {
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
  }
  friend bool operator>(const ipoint& lhs, const ipoint& rhs) {
    return rhs < lhs;
  }
  friend bool operator<=(const ipoint& lhs, const ipoint& rhs) {
    return !(lhs > rhs);
  }
  friend bool operator>=(const ipoint& lhs, const ipoint& rhs) {
    return !(lhs < rhs);
  }

  friend std::istream& operator>>(std::istream& is, ipoint& v) {
    return is >> v.x >> v.y;
  }
  friend std::ostream& operator<<(std::ostream& os, const ipoint& v) {
    return os << v.x << " " << v.y;
  }
};

long long dot(const ipoint& lhs, const ipoint& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}
long long cross(const ipoint& lhs, const ipoint& rhs) {
  return lhs.x * rhs.y - lhs.y * rhs.x;
}

bool is_parallel(const ipoint& lhs, const ipoint& rhs) {
  return dot(lhs, rhs) == 0;
}
bool is_orthogonal(const ipoint& lhs, const ipoint& rhs) {
  return cross(lhs, rhs) == 0;
}

bool argless(const ipoint& lhs, const ipoint& rhs) {
  int lo = lhs.ort(), ro = rhs.ort();
  if (lo != ro) return lo < ro;
  return cross(lhs, rhs) > 0;
}

}  // namespace cp