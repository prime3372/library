#pragma once

#include <array>
#include <cassert>
#include <functional>
#include <string>
#include <type_traits>
#include <vector>

namespace cp {

namespace internal {

template <int char_size, class derived>
struct trie_tree_base {
public:
  trie_tree_base() : trie_tree_base(std::vector<std::string>()) {}
  explicit trie_tree_base(const std::vector<std::string>& v) {
    extend();
    for (auto& s : v) insert(s);
  }

  int insert(const std::string& s) {
    int v = 0;
    for (char c : s) {
      mid[v]++;
      int k = index(c);
      if (to[v][k] == -1) {
        to[v][k] = n;
        extend();
        par.back() = v;
      }
      v = to[v][k];
    }
    end[v]++;
    return v;
  }

  std::vector<int> search(const std::string& s, int from = 0) const {
    assert(0 <= from && from < n);
    std::vector<int> res(1, from);
    for (char c : s) {
      int v = res.back(), k = index(c);
      if (to[v][k] == -1) break;
      res.push_back(to[v][k]);
    }
    return res;
  }

  const std::array<int, char_size>& operator[](int v) const {
    assert(0 <= v && v < n);
    return to[v];
  }
  int parent(int v) const {
    assert(0 <= v && v < n);
    return par[v];
  }

  int count(int v) const {
    assert(0 <= v && v < n);
    return end[v];
  }
  int prefix(int v) const {
    assert(0 <= v && v < n);
    return mid[v] + end[v];
  }
  int proper_prefix(int v) const {
    assert(0 <= v && v < n);
    return mid[v];
  }

  int size() const { return n; }

private:
  int n = 0;
  std::vector<std::array<int, char_size>> to;
  std::vector<int> par, mid, end;

  static constexpr int index(char c) {
    return derived::index(c); // CRTP
  }

  void extend() {
    n++;
    to.emplace_back();
    to.back().fill(-1);
    par.push_back(-1);
    mid.push_back(0);
    end.push_back(0);
  }
};

constexpr int lower_offset(char c) {
  assert('a' <= c && c <= 'z');
  return c - 'a';
}

constexpr int upper_offset(char c) {
  assert('A' <= c && c <= 'Z');
  return c - 'A';
}

} // namespace internal

template <int char_size, auto is_upper = false>
struct trie_tree : public internal::trie_tree_base<char_size,
                                                   trie_tree<char_size, is_upper>> {
  static_assert(std::is_convertible_v<decltype(is_upper), bool>);
  using internal::trie_tree_base<char_size,
                                 trie_tree<char_size, is_upper>>::trie_tree_base;
public:
  static constexpr int index(char c) {
    return is_upper ? internal::upper_offset(c) : internal::lower_offset(c);
  }
};

template <int char_size, auto offset>
  requires std::is_convertible_v<decltype(offset), std::function<int(char)>>
struct trie_tree<char_size, offset> : internal::trie_tree_base<char_size,
                                                               trie_tree<char_size, offset>> {
  using internal::trie_tree_base<char_size,
                                 trie_tree<char_size, offset>>::trie_tree_base;
public:
  static constexpr int index(char c) {
    return offset(c);
  }
};

} // namespace cp