#pragma once

#include <array>
#include <bitset>
#include <cassert>
#include <limits>
#include <vector>

namespace cp {

template <int bit_size> struct BinaryTrie {
  using Bitset = std::bitset<bit_size>;

 public:
  BinaryTrie() { nodes.push_back(Node(-1)); }

  int insert(const Bitset& s) {
    int v = 0;
    nodes[v].sub++;
    for (int i = bit_size - 1; i >= 0; i--) {
      if (nodes[v].to[s[i]] == -1) {
        nodes[v].to[s[i]] = int(nodes.size());
        nodes.push_back(Node(v));
      }
      v = nodes[v].to[s[i]];
      nodes[v].sub++;
    }
    return v;
  }

  bool erase(const Bitset& s) {
    if (count(s) == 0) return false;
    int v = 0;
    nodes[v].sub--;
    for (int i = bit_size - 1; i >= 0; i--) {
      int nv = nodes[v].to[s[i]];
      nodes[nv].sub--;
      if (nodes[nv].sub == 0) {
        nodes[v].to[s[i]] = -1;
        nodes[nv].par = -1;
      }
      v = nv;
    }
    return true;
  }

  int count(const Bitset& s) const {
    int v = 0;
    for (int i = bit_size - 1; i >= 0; i--) {
      v = nodes[v].to[s[i]];
      if (v == -1) return 0;
    }
    return nodes[v].sub;
  }

  Bitset kth_elem(int k, const Bitset& xor_val = Bitset{}) const {
    assert(0 <= k && k < nodes[0].sub);
    int v = 0;
    Bitset res;
    for (int i = bit_size - 1; i >= 0; i--) {
      int left = nodes[v].to[xor_val[i]];
      int right = nodes[v].to[!xor_val[i]];
      if (left == -1 || k >= nodes[left].sub) {
        res.set(i);
        if (left != -1) k -= nodes[left].sub;
        v = right;
      } else {
        v = left;
      }
    }
    return res;
  }

  Bitset min(const Bitset& xor_val = Bitset{}) const {
    return kth_elem(0, xor_val);
  }
  Bitset max(const Bitset& xor_val = Bitset{}) const {
    return kth_elem(nodes[0].sub - 1, xor_val);
  }

  int range_count(const Bitset& lower, const Bitset& upper,
                  const Bitset& xor_val = Bitset{}) const {
    assert(lower.to_string() <= upper.to_string());
    auto f = [&](const Bitset& s) {
      int v = 0, cnt = 0;
      for (int i = bit_size - 1; i >= 0; i--) {
        if (v == -1) break;
        int left = nodes[v].to[xor_val[i]];
        int right = nodes[v].to[!xor_val[i]];
        if (s[i]) {
          if (left != -1) cnt += nodes[left].sub;
          v = right;
        } else {
          v = left;
        }
      }
      return cnt;
    };
    return f(upper) - f(lower);
  }

 private:
  struct Node {
    int par, sub;
    std::array<int, 2> to;
    Node(int p) : par(p), sub(0) { to.fill(-1); }
  };

  std::vector<Node> nodes;
};

}  // namespace cp