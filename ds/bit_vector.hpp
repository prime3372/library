#pragma once

#include <bit>
#include <vector>

namespace cp {

class bit_vector {
 public:
  bit_vector() {}
  explicit bit_vector(int _n) : n(_n), block(n / w + 1), count(n / w + 1) {}

  void set(int i) {
    assert(0 <= i && i < n);
    block[i / w] |= 1LL << (i % w);
  }
  void build() {
    for (int i = 1; i < int(block.size()); i++) {
      count[i] = count[i - 1] + std::popcount(block[i - 1]);
    }
  }

  bool operator[](int i) const {
    assert(0 <= i && i < n);
    return (block[i / w] & (1ULL << (i % w))) != 0;
  }

  int rank0(int i) const {
    assert(0 <= i && i <= n);
    return i - rank1(i);
  }
  int rank1(int i) const {
    assert(0 <= i && i <= n);
    return count[i / w] + std::popcount(block[i / w] & ((1ULL << (i % w)) - 1));
  }
  int zeros() const { return rank0(n); }
  int ones() const { return rank1(n); }

 private:
  static constexpr int w = 64;
  int n;
  std::vector<unsigned long long> block;
  std::vector<int> count;
};

}  // namespace cp