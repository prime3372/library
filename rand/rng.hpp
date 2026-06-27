#pragma once

#include <cassert>
#include <random>

std::random_device seed_gen;
std::mt19937_64 mt(seed_gen());
long long rng(long long r) {
  assert(1 <= r);
  return mt() % r;
}
long long rng(long long l, long long r) {
  assert(l < r);
  return (long long)(mt() % (r - l)) + l;
}
