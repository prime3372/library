#pragma once

#include <array>
#include <cassert>
#include <cctype>
#include <string>
#include <vector>

namespace cp {

template <bool is_upper> struct trie_tree {
public:
  static constexpr int sigma = 26;
  static constexpr char base = is_upper ? 'A' : 'a';

  trie_tree() : trie_tree(std::vector<std::string>()) {}
  explicit trie_tree(std::vector<std::string> v) {
    extend();
    for (auto s : v) insert(s);
  }

  int insert(const std::string& s) {
    int v = 0;
    for (int i = 0; i < int(s.size()); i++) {
      assert(is_upper ? std::isupper(s[i]) : std::islower(s[i]));
      mid[v]++;
      int k = s[i] - base;
      if (ch[v][k] == -1) {
        ch[v][k] = n;
        extend();
        par.back() = v;
      }
      v = ch[v][k];
    }
    end[v]++;
    return v;
  }

  std::vector<int> search(const std::string& s, int from = 0) const {
    assert(0 <= from && from < n);
    std::vector<int> res(s.size() + 1);
    res[0] = from;
    for (int i = 0; i < int(s.size()); i++) {
      int k = s[i] - base;
      res[i + 1] = ch[res[i]][s[i]];
      if (res[i + 1] == -1) break;
    }
    return res;
  }

  const std::array<int, sigma>& operator[](int v) const {
    assert(0 <= v && v < n);
    return ch[v];
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
  std::vector<std::array<int, sigma>> ch;
  std::vector<int> par, mid, end;

  void extend() {
    n++;
    ch.emplace_back();
    ch.back().fill(-1);
    par.push_back(-1);
    mid.push_back(0);
    end.push_back(0);
  }
};

} // namespace cp