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
      pre[v]++;
      int k = index(c);
      if (to[v][k] == -1) {
        to[v][k] = n;
        extend();
        par.back() = v;
      }
      v = to[v][k];
    }
    pre[v]++;
    cnt[v]++;
    return v;
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
    return cnt[v];
  }
  int prefix(int v) const {
    assert(0 <= v && v < n);
    return pre[v];
  }

  int size() const { return n; }

private:
  int n = 0;
  std::vector<std::array<int, char_size>> to;
  std::vector<int> par, pre, cnt;

  static constexpr int index(char c) {
    return derived::index(c); // CRTP
  }

  void extend() {
    n++;
    to.emplace_back();
    to.back().fill(-1);
    par.push_back(-1);
    pre.push_back(0);
    cnt.push_back(0);
  }
};

} // namespace internal

template <int char_size, auto offset = 'a'>
struct trie_tree {};

template <int char_size, char offset>
struct trie_tree<char_size, offset>
: public internal::trie_tree_base<char_size, trie_tree<char_size, offset>> {
public:
  using internal::trie_tree_base<char_size, trie_tree<char_size, offset>>
        ::trie_tree_base;
  static constexpr int index(char c) {
    return c - offset;
  }
};

template <int char_size, auto offset>
  requires std::is_convertible_v<decltype(offset), std::function<int(char)>>
struct trie_tree<char_size, offset>
: public internal::trie_tree_base<char_size, trie_tree<char_size, offset>> {
public:
  using internal::trie_tree_base<char_size, trie_tree<char_size, offset>>
        ::trie_tree_base;
  static constexpr int index(char c) {
    return offset(c);
  }
};

} // namespace cp