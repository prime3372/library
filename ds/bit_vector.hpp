#pragma once

#include <bit>
#include <cassert>
#include <vector>

namespace cp {

class bit_vector {
 public:
  bit_vector() {}
  explicit bit_vector(int _n) : n(_n), block(n / 64 + 1), count(n / 64 + 1) {}

  void set(int i) {
    assert(0 <= i && i < n);
    block[i / 64] |= mask(i % 64);
  }

  void build() {
    for (int i = 0; i < int(block.size()) - 1; i++) {
      count[i + 1] = count[i] + std::popcount(block[i]);
    }
  }

  bool operator[](int i) const {
    assert(0 <= i && i < n);
    return (block[i / 64] & mask(i % 64)) != 0;
  }

  int rank0(int i) const {
    assert(0 <= i && i <= n);
    return i - rank1(i);
  }
  int rank1(int i) const {
    assert(0 <= i && i <= n);
    return count[i / 64] + std::popcount(block[i / 64] & (mask(i % 64) - 1));
  }

 private:
  int n;
  std::vector<unsigned long long> block;
  std::vector<int> count;

  static unsigned long long mask(int pos) { return 1ULL << pos; }
};

}  // namespace cp