#pragma once

#include <cassert>
#include <cctype>
#include <queue>
#include <string>
#include <vector>

#include "trie_tree.hpp"

namespace cp {

struct aho_corasick : public trie_tree {
public:
  using trie_tree::trie_tree;
  using trie_tree::size;

  void build() {
    lnk.resize(size());
    lnk[0] = -1;
    std::queue<int> que;
    que.push(0);
    while (!que.empty()) {
      int v = que.front();
      que.pop();
      for (auto [c, u] : (*this)[v].enumerate()) {
        int l = lnk[v];
        while (l != -1) {
          if ((*this)[l].count(c)) {
            lnk[u] = (*this)[l][c];
            break;
          }
          l = lnk[l];
        }
        que.push(u);
      }
    }
  }

  std::vector<int> move(const std::string& s, int from = 0) const {
    assert(0 <= from && from < size());
    std::vector<int> res(1, from);
    for (char c : s) {
      if (!(*this)[res.back()].count(c)) {
        res.push_back((*this)[res.back()][c]);
      } else {
        res.push_back(lnk[res.back()]);
      }
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