#pragma once

#include <array>
#include <cassert>
#include <string>
#include <type_traits>
#include <vector>

template <int char_size, auto offset = [](char c) { return c - 'a'; }>
class trie {
 public:
  trie() { nodes.push_back(node(-1)); }

  int insert(const std::string& s) {
    int v = 0;
    nodes[v].mid++;
    for (char c : s) {
      int i = _offset(c);
      if (nodes[v].to[i] == -1) {
        nodes[v].to[i] = size();
        nodes.push_back(node(v));
      }
      v = nodes[v].to[i];
      nodes[v].mid++;
    }
    nodes[v].end++;
    return v;
  }

  // @note Edges rendered unnecessary by this function are removed, but vertices
  // are not.
  bool erase(const std::string& s) {
    if (count(s) == 0) return false;
    int v = 0;
    nodes[v].mid--;
    for (char c : s) {
      int i = _offset(c);
      int nv = nodes[v].to[i];
      nodes[nv].mid--;
      if (nodes[nv].mid == 0) {
        nodes[v].to[i] = -1;
        nodes[nv].par = -1;
      }
      v = nv;
    }
    nodes[v].end--;
    return true;
  }

  int count(const std::string& s) const {
    int v = search(s);
    return v == -1 ? 0 : count(v);
  }
  int count(int v) const {
    assert(0 <= v && v < int(nodes.size()));
    return nodes[v].end;
  }

  int count_prefix(const std::string& s) const {
    int v = search(s);
    return v == -1 ? 0 : count_prefix(v);
  }
  int count_prefix(int v) const {
    assert(0 <= v && v < int(nodes.size()));
    return nodes[v].mid;
  }

  const std::array<int, char_size>& operator[](int v) const {
    assert(0 <= v && v < int(nodes.size()));
    return nodes[v].to;
  }
  int parent(int v) const {
    assert(0 <= v && v < int(nodes.size()));
    return nodes[v].par;
  }

  int search(const std::string& s, int v = 0) const {
    assert(0 <= v && v < int(nodes.size()));
    for (char c : s) {
      v = (*this)[v][_offset(c)];
      if (v == -1) return -1;
    }
    return v;
  }

  int size() const { return int(nodes.size()); }

 private:
  struct node {
    std::array<int, char_size> to;
    int par, end, mid;

    node(int p) : par(p), end(0), mid(0) { to.fill(-1); }
  };

  std::vector<node> nodes;

  int _offset(char c) const {
    int i = offset(c);
    assert(0 <= i && i < char_size);
    return i;
  }
};