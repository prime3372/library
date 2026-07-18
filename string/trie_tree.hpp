#pragma once

#include <vector>
#include <string>
#include <array>
#include <type_traits>

template <int char_size, auto offset = 'a'>
class trie_tree {
public:
  trie_tree() { nodes.push_back(node(-1)); }
  trie_tree(const std::vector<std::string>& vec) : trie_tree() {
    for (const auto& s : vec) insert(s);
  }

  int insert(const std::string& s) {
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

  bool erase(const std::string& s) {
    if (count(s) == 0) return false;
    int v = 0;
    nodes[v].mid--;
    for (char c : s) {
      size_t i = index(c);
      int nv = nodes[v].to[i];
      nodes[nv].mid--;
      if (nodes[nv].mid == 0) {
        nodes[v].to[i] = -1;
      }
      v = nv;
    }
    nodes[v].end--;
    return true;
  }

  const std::array<int, char_size>& operator[](int v) const {
    return nodes[v].to;
  }

  int next(int v, char c) const {
    int u = nodes[v].to[index(c)];
    if (u == -1 || nodes[u].pre == 0) return -1;
    return u;
  }

  int parent(int v) const { return nodes[v].par; }

  int search(int v, const std::string& s) const {
    for (char c : s) {
      v = next(v, c);
      if (v == -1) return -1;
    }
    return v;
  }
  int search(const std::string s) const { return search(0, s); }

  int count(int v) const { return nodes[v].end; }
  int count(const std::string& s) const {
    int v = search(s);
    return v == -1 ? 0 : count(v);
  }

  int prefix(int v) const { return nodes[v].mid; }
  int prefix(const std::string s) const {
    int v = search(s);
    return v == -1 ? 0 : prefix(v);
  }

  int size() const { return int(nodes.size()); }

protected:
  constexpr int index(char c) const {
    if constexpr (std::is_invocable_v<decltype(offset), char>) {
      return offset(c);
    } else {
      assert(0 <= c - offset && c - offset < char_size);
      return c - offset;
    }
  }

private:
  struct node {
    std::array<int, char_size> to;
    int par, end, mid;

    node(int p) : par(p), end(0), mid(0) { to.fill(-1); }
  };

  std::vector<node> nodes;
};