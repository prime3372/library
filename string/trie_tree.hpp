#pragma once

#include <array>
#include <cassert>
#include <cctype>
#include <string>
#include <utility>
#include <vector>

#include "ds/hash_map.hpp"

namespace cp {

struct trie_tree {
public:
  trie_tree() : trie_tree(std::vector<std::string>()) {}
  explicit trie_tree(std::vector<std::string> v) {
    extend();
    for (auto s : v) insert(s);
  }

  int insert(const std::string& s) {
    int v = 0;
    for (char c : s) {
      mid[v]++;
      if (!to[v].count(c)) {
        to[v][c] = n;
        extend();
        par.back() = v;
      }
      v = to[v][c];
    }
    end[v]++;
    return v;
  }

  std::vector<int> search(const std::string& s, int from = 0) const {
    assert(0 <= from && from < n);
    std::vector<int> res(1, from);
    for (char c : s) {
      if (!to[res.back()].count(c)) {
        res.push_back(-1);
        break;
      }
      res.push_back(to[res.back()][c]);
    }
    return res;
  }

  const hash_map<char, int>& operator[](int v) const {
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
  std::vector<hash_map<char, int>> to;
  std::vector<int> par, mid, end;

  void extend() {
    n++;
    to.emplace_back();
    to.back().set_default(-1);
    par.push_back(-1);
    mid.push_back(0);
    end.push_back(0);
  }
};

} // namespace cp