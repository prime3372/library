#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

struct perm {
public:
  perm(int _n) : n(_n), p(_n) {
    std::iota(p.begin(), p.end(), 0);
  }
  perm(std::vector<int> _p) : n(_n), p(_p) {}

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
    perm r(n);
    for (int i = 0; i < n; i++) r[i] = q[p[i]];
    return r;
  }
  perm operator-() const {
    perm r(n);
    for (int i = 0; i < n; ++i) r[p[i]] = i;
    return r;
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
