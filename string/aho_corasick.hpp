#pragma once

#include <cassert>
#include <string>
#include <vector>

#include "ds/simple_queue.hpp"
#include "string/trie_tree.hpp"

namespace cp {

template <int char_size, auto offset = 'a'>
class aho_corasick : public trie_tree<char_size, offset> {
 public:
  using trie_tree<char_size, offset>::trie_tree;
  using trie_tree<char_size, offset>::size;

  void build() {
    lnk.resize(size());
    lnk[0] = -1;
    simple_queue<int> que;
    que.push(0);
    while (!que.empty()) {
      int v = que.front();
      que.pop();
      for (int i = 0; i < char_size; i++) {
        int u = (*this)[v][i], l = lnk[v];
        if (u == -1) continue;
        que.push(u);
        while (l != -1) {
          if ((*this)[l][i] != -1) {
            lnk[u] = (*this)[l][i];
            break;
          }
          l = lnk[l];
        }
      }
    }
  }

  int link(int v) const {
    assert(0 <= v && v < size());
    return lnk[v];
  }

 private:
  std::vector<int> lnk;
};

} // namespace cp