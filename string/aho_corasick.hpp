#pragma once

#include <cassert>
#include <cctype>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

#include "trie_tree.hpp"

namespace cp {

template <bool is_upper>
struct aho_corasick : public trie_tree<is_upper> {
public:
  using trie_tree<is_upper>::trie_tree;
  using trie_tree<is_upper>::sigma;
  using trie_tree<is_upper>::base;
  using trie_tree<is_upper>::size;

  void build() {
    lnk.resize(size());
    std::queue<std::tuple<int, int, int>> que;
    for (int i = 0; i < sigma; i++) {
      if ((*this)[0][i] != -1) {
        que.emplace((*this)[0][i], 0, i);
      }
    }
    while (!que.empty()) {
      auto [v, p, k] = que.front();
      que.pop();
      for (int i = 0; i < sigma; i++) {
        if ((*this)[v][i] != -1) que.emplace((*this)[v][i], v, i);
      }
      if (p == 0) continue;
      p = lnk[p];
      while (p && (*this)[p][k] == -1) p = lnk[p];
      lnk[v] = (*this)[p][k] != -1 ? (*this)[p][k] : 0;
    }
  }

  std::vector<int> move(const std::string& s, int from = 0) const {
    assert(0 <= from && from < size());
    std::vector<int> res(s.size() + 1);
    res[0] = from;
    for (int i = 0; i < int(s.size()); i++) {
      int k = s[i] - base;
      res[i + 1] = (*this)[res[i]][k] != -1 ? (*this)[res[i]][k] : lnk[res[i]];
    }
    return res;
  }

  int link(int v) const {
    assert(0 <= v && v < size());
    return lnk[v];
  }

private:
  std::vector<int> lnk;
};

} // namespace cp