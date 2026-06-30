#pragma once

#include <algorithm>
#include <cassert>
#include <concepts>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace internal {

std::random_device seed_gen;
std::mt19937_64 mt(seed_gen());

template <class T, class derived> struct rng_base {
public:
  struct random_pair : std::pair<T, T> {
    friend rng_base;
    friend derived;
  public:
    friend ostream& operator<<(ostream& os, const random_pair& p) {
      os << p.first << " " << p.second;
      return os;
    }
  private:
    random_pair() : std::pair<T, T>() {}
    random_pair(T f, T s) : std::pair<T, T>(f, s) {}
  };

  struct random_seq : public std::vector<T> {
    friend rng_base;
    friend derived;
  public:
    friend ostream& operator<<(ostream& os, const random_seq& sq) {
      for (int i = 0; i < int(sq.size()); i++) {
        os << sq[i] << " ";
      }
      return os;
    }
  private:
    random_seq() : random_seq(0) {}
    random_seq(int n) : std::vector<T>(n) {}
  };

  rng_base() = delete;

  static T rand(T l, T r) {
    assert(l < r);
    return derived::rand(l, r);
  }

  static random_pair pair(T l, T r) {
    assert(l < r);
    return random_pair{rand(l, r), rand(l, r)};
  }

  static random_pair intvl(T l, T r) {
    assert(l < r);
    random_pair p = pair(l, r);
    if (p.first > p.second) std::swap(p.first, p.second);
    return p;
  }

  static random_seq seq(int n, T l, T r) {
    assert(0 <= n && (n == 0 || l < r));
    random_seq sq(n);
    for (int i = 0; i < n; i++) {
      sq[i] = rand(l, r);
    }
    return sq;
  }

  static random_seq sorted_seq(int n, T l, T r) {
    assert(0 <= n && (n == 0 || l < r));
    random_seq res = seq(n, l, r);
    std::sort(res.begin(), res.end());
    return res;
  }

  static random_seq rsorted_seq(int n, T l, T r) {
    assert(0 <= n && (n == 0 || l < r));
    random_seq res = seq(n, l, r);
    std::sort(res.rbegin(), res.rend());
    return res;
  }
};

} // namespace internal

template <class> struct rng;

template <std::integral T> struct rng<T> : public internal::rng_base<T, rng<T>> {
  using random_seq = typename internal::rng_base<T, rng>::random_seq;
  static T rand(T l, T r) {
    assert(l < r);
    return T(internal::mt() % (r - l)) + l;
  }
  static random_seq perm(int n) {
    random_seq p(n);
    std::iota(p.begin(), p.end(), T(0));
    std::shuffle(p.begin(), p.end(), internal::mt);
    return p;
  }
  rng() = delete;
};

template <std::floating_point T> struct rng<T> : public internal::rng_base<T, rng<T>> {
  static T rang(T l, T r) {
    assert(l < r);
    return std::uniform_real_distribution<T>(l, r)(internal::mt);
  }
  rng() = delete;
};

template <> struct rng<char> {
  static int rand(int l, int r) {
    assert(l < r);
    return int(internal::mt() % (r - l)) + l;
  }
  static std::string str(int n, bool upper = false) {
    std::string res(n, '?');
    for (int i = 0; i < n; i++) {      
      res[i] = char((upper ? 'A' : 'a') + rand(0, 26));
    }
    return res;
  }
  static std::string str(int n, std::string s) {
    std::string res(n, '?');
    for (int i = 0; i < n; i++) {
      res[i] = s[rand(0, int(s.size()))];
    }
    return res;
  }
  static std::string dec(int n) {
    std::string res(n, '?');
    for (int i = 0; i < n; i++) {
      res[i] = char('0' + rand(0, 10));
    }
    return res;
  }
  rng() = delete;
};