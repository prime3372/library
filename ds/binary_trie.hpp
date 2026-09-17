#pragma once

#include <array>
#include <bitset>
#include <cassert>
#include <limits>
#include <vector>

namespace cp {

template <int bit_size> class binary_trie {
  using bs = std::bitset<bit_size>;

 public:
  binary_trie() { nodes.push_back(node(-1)); }

  int insert(const bs& s) {
    int v = 0;
    nodes[v].sub++;
    for (int i = bit_size - 1; i >= 0; i--) {
      if (nodes[v].to[s[i]] == -1) {
        nodes[v].to[s[i]] = int(nodes.size());
        nodes.push_back(node(v));
      }
      v = nodes[v].to[s[i]];
      nodes[v].sub++;
    }
    return v;
  }

  bool erase(const bs& s) {
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

  int count(const bs& s) const {
    int v = 0;
    for (int i = bit_size - 1; i >= 0; i--) {
      v = nodes[v].to[s[i]];
      if (v == -1) return 0;
    }
    return nodes[v].sub;
  }

  bs kth_elem(int k, const bs& xor_val = bs()) const {
    assert(0 <= k && k < nodes[0].sub);
    int v = 0;
    bs res;
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

  bs min(const bs& xor_val = bs()) const { return kth_elem(0, xor_val); }
  bs max(const bs& xor_val = bs()) const {
    return kth_elem(nodes[0].sub - 1, xor_val);
  }

  int range_count(const bs& lower, const bs& upper,
                  const bs& xor_val = bs()) const {
    assert(lower.to_string() <= upper.to_string());
    auto f = [&](const bs& s) {
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
  struct node {
    int par, sub;
    std::array<int, 2> to;

    node() : node(-1) {}
    explicit node(int p) : par(p), sub(0) { to.fill(-1); }
  };

  std::vector<node> nodes;
};

}  // namespace cp