#pragma once

#include <cassert>
#include <functional>
#include <vector>

namespace cp {

class cartesian_tree {
 public:
  cartesian_tree() {}
  template <class T, class Compare = std::less<T>>
  explicit cartesian_tree(const std::vector<T>& a,
                          Compare compare = Compare()) {
    build(a, compare);
  }

  int root = -1;
  std::vector<int> left, right, parent, size;

  // @note The smallest element becomes the root.
  // @note For equivalent elements, the one with the smaller index is smaller.
  // @note `parent[root]` is `-1`.
  template <class T, class Compare = std::less<T>>
  void build(const std::vector<T>& a, Compare compare = Compare()) {
    if (a.empty()) return;
    int n = int(a.size());

    left.assign(n, -1);
    right.assign(n, -1);
    std::vector<int> st;
    for (int i = 0; i < n; i++) {
      int k = -1;
      while (!st.empty() && compare(a[i], a[st.back()])) {
        k = st.back();
        st.pop_back();
      }
      if (!st.empty()) right[st.back()] = i;
      left[i] = k;
      st.push_back(i);
    }
    root = st[0];

    parent.resize(n);
    parent[root] = -1;
    for (int i = 0; i < n; i++) {
      if (left[i] != -1) parent[left[i]] = i;
      if (right[i] != -1) parent[right[i]] = i;
    }

    size.resize(n);
    auto dfs = [&](auto self, int i) -> int {
      size[i] = 1;
      if (left[i] != -1) size[i] += self(self, left[i]);
      if (right[i] != -1) size[i] += self(self, right[i]);
      return size[i];
    };
    dfs(dfs, root);
  }
};

}  // namespace cp