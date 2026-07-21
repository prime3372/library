#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

namespace cp {

struct perm {
public:
  perm(int _n) : n(_n), p(_n) {
    std::iota(p.begin(), p.end(), 0);
  }
  perm(std::vector<int> _p) : n(int(_p.size())), p(_p) {}

  int& operator[](int i) {
    assert(0 <= i && i < n);
    return p[i];
  }
  int operator[](int i) const {
    assert(0 <= i && i < n);
    return p[i];
  }

  friend perm operator+(const perm& q, const perm& p) {
    assert(p.n == q.n);
    perm r(p.n);
    for (int i = 0; i < p.n; i++) r[i] = q[p[i]];
    return r;
  }

  perm operator-() const {
    perm q(n);
    for (int i = 0; i < n; ++i) q[p[i]] = i;
    return q;
  }
  
  friend perm operator-(const perm& q, const perm& p) {
    assert(p.n == q.n);
    return q + -p;
  }

  bool operator++() {
    return std::next_permutation(p.begin(), p.end());
  }

private:
  int n;
  std::vector<int> p;
};

} // namespace cp