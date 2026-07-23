#pragma once

#include <array>
#include <cassert>
#include <type_traits>
#include <vector>

template <int char_size, auto offset = 'a'>
class trie_tree {
public:
  trie_tree() { nodes.push_back(node(-1)); }

  template <class Str>
  int insert(const Str& s) {
    int v = 0;
    nodes[v].mid++;
    for (char c : s) {
      int i = index(c);
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

  template <class Str>
  bool erase(const Str& s) {
    if (count(s) == 0) return false;
    int v = 0;
    nodes[v].mid--;
    for (char c : s) {
      size_t i = index(c);
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

  template <class Str>
  int count(const Str& s) const {
    int v = search(s);
    return v == -1 ? 0 : count(v);
  }
  int count(int v) const {
    return nodes[v].end;
  }

  template <class Str>
  int prefix(const Str& s) const {
    int v = search(s);
    return v == -1 ? 0 : prefix(v);
  }
  int prefix(int v) const {
    return nodes[v].mid;
  }

  template <class Str>
  int search(const Str& s) const {
    return search(0, s);
  }
  template <class Str>
  int search(int v, const Str& s) const {
    for (char c : s) {
      v = next(v, c);
      if (v == -1) return -1;
    }
    return v;
  }

  const std::array<int, char_size>& operator[](int v) const {
    return nodes[v].to;
  }

  int next(int v, char c) const {
    return nodes[v].to[index(c)];
  }

  int parent(int v) const {
    return nodes[v].par;
  }

  int size() const {
    return int(nodes.size());
  }

protected:
  constexpr int index(char c) const {
    // offset can be a function
    if constexpr (std::is_invocable_v<decltype(offset), char>) {
      int idx = offset(c);
      assert(0 <= idx && idx < char_size);
      return idx;
    }

    assert(0 <= c - offset && c - offset < char_size);
    return c - offset;
  }

private:
  struct node {
    std::array<int, char_size> to;
    int par, end, mid;

    node(int p) : par(p), end(0), mid(0) { to.fill(-1); }
  };

  std::vector<node> nodes;
};