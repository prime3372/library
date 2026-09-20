#pragma once

#include <array>
#include <cassert>
#include <string>
#include <vector>

#include "ds/simple_queue.hpp"

namespace cp {

template <int char_size, char offset = 'a'> class aho_corasick {
 public:
  class node {
   public:
    int parent() const { return par; }
    int link() const { return lnk; }
    int operator[](int i) const {
      assert(0 <= i && i < char_size);
      return to[i];
    }

   private:
    friend aho_corasick;
    int par, lnk;
    std::array<int, char_size> to;
    node(int p) : par(p), lnk(0) { to.fill(-1); }
  };

  aho_corasick() { nodes.push_back(node(-1)); }

  int add(const std::string& s) {
    int v = 0;
    for (char c : s) {
      int i = c - offset;
      assert(0 <= i && i < char_size);
      if (nodes[v].to[i] == -1) {
        nodes[v].to[i] = size();
        nodes.push_back(node(v));
      }
      v = nodes[v].to[i];
    }
    return v;
  }

  void init() {
    simple_queue<int> que;
    for (int i = 0; i < char_size; i++) {
      if (nodes[0].to[i] != -1) {
        que.push(nodes[0].to[i]);
      } else {
        nodes[0].to[i] = 0;
      }
    }
    while (!que.empty()) {
      int v = que.front();
      que.pop();
      for (int i = 0; i < char_size; i++) {
        int& nv = nodes[v].to[i];
        if (nv != -1) {
          nodes[nv].lnk = nodes[nodes[v].lnk].to[i];
          que.push(nv);
        } else {
          nv = nodes[nodes[v].lnk].to[i];
        }
      }
    }
    initialized = true;
  }

  const node& operator[](int v) const {
    assert(0 <= v && v < size());
    return nodes[v];
  }

  int size() const { return int(nodes.size()); }

 private:
  std::vector<node> nodes;
  bool initialized = false;
};

}  // namespace cp