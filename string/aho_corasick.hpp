#pragma once

#include <cassert>
#include <queue>
#include <string>
#include <vector>

#include "trie_tree.hpp"

namespace cp {

template <int char_size, auto offset = 'a'>
struct aho_corasick : public trie_tree<char_size, offset> {
public:
  using trie_tree<char_size, offset>::trie_tree;
  using trie_tree<char_size, offset>::size;
  
  void build() {
    lnk.resize(size());
    lnk[0] = -1;
    std::queue<int> que;
    que.push(0);
    while (!que.empty()) {
      int v = que.front();
      que.pop();
      for (int i = 0; i < char_size; i++) {
        int u = (*this)[v][i], l = lnk[v];
        if (u == -1) continue;
        while (l != -1) {
          if ((*this)[l][i] != -1) {
            lnk[u] = (*this)[l][i];
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
      int v = res.back(), k = this->index(c);
      if ((*this)[v][k] != -1) {
        res.push_back((*this)[v][k]);
      } else {
        res.push_back(lnk[v]);
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