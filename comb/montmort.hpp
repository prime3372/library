#pragma once

#include <cassert>
#include <vector>

namespace cp {

// https://en.wikipedia.org/wiki/Derangement#Counting_derangements
template <class T> std::vector<T> montmort(int n) {
  assert(0 <= n);
  if (n == 0) return {1};
  std::vector<T> a(n + 1);
  a[0] = 1;
  a[1] = 0;
  for (int i = 2; i <= n; i++) {
    a[i] = (i - 1) * (a[i - 1] + a[i - 2]);
  }
  return a;
}

}  // namespace cp