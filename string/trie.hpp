#pragma once

#include <array>
#include <cassert>
#include <string>
#include <type_traits>
#include <vector>

template <int char_size, char offset = 'a'> class trie {
 public:
  class node {
   public:
    int parent() const { return par; }
    int count() const { return cnt; }
    int subtree_sum() const { return sub; }
    int operator[](int i) const {
      assert(0 <= i && i < char_size);
      return to[i];
    }

   private:
    friend trie;
    int par, cnt, sub;
    std::array<int, char_size> to;
    node(int p) : par(p), cnt(0), sub(0) { to.fill(-1); }
  };

  trie() { nodes.push_back(node(-1)); }

  int insert(const std::string& s) {
    int v = 0;
    nodes[v].sub++;
    for (char c : s) {
      int i = index(c);
      if (nodes[v].to[i] == -1) {
        nodes[v].to[i] = size();
        nodes.push_back(node(v));
      }
      v = nodes[v].to[i];
      nodes[v].sub++;
    }
    nodes[v].cnt++;
    return v;
  }

  // @note This function deletes edges that are no longer needed, but it does
  // not delete vertices.
  bool erase(const std::string& s) {
    if (count(s) == 0) return false;
    int v = 0;
    nodes[v].sub--;
    for (char c : s) {
      int i = index(c);
      int nv = nodes[v].to[i];
      nodes[nv].sub--;
      if (nodes[nv].sub == 0) {
        nodes[v].to[i] = -1;
        nodes[nv].par = -1;
      }
      v = nv;
    }
    nodes[v].cnt--;
    return true;
  }

  const node& operator[](int v) const {
    assert(0 <= v && v < size());
    return nodes[v];
  }

  int size() const { return int(nodes.size()); }

 private:
  std::vector<node> nodes;

  int index(char c) const {
    int i = c - offset;
    assert(0 <= i && i < char_size);
    return i;
  }
};