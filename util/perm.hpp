#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

namespace cp {

struct perm : public std::vector<int> {
  perm() {}
  explicit perm(int _n) {
    std::iota(begin(), end(), 0);
  }

  friend perm operator+(const perm& q, const perm& p) {
    assert(p.size() == q.size());
    perm r(p.size());
    for (int i = 0; i < int(p.size()); i++) r[i] = q[p[i]];
    return r;
  }

  perm operator-() const {
    perm q(size());
    for (int i = 0; i < int(size()); i++) q[(*this)[i]] = i;
    return q;
  }
  
  friend perm operator-(const perm& q, const perm& p) {
    assert(p.size() == q.size());
    return q + -p;
  }

  bool operator++() {
    return std::next_permutation(begin(), end());
  }

  bool operator--() {
    return std::prev_permutation(begin(), end());
  }
};

} // namespace cp