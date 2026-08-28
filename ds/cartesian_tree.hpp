#pragma once

#include <cassert>
#include <functional>
#include <vector>

namespace cp {

class cartesian_tree {
 public:
  cartesian_tree() {}
  template <class T, class Comp = std::less<T>>
  explicit cartesian_tree(const std::vector<T>& a, Comp comp = Comp()) {
    build(a, comp);
  }

  int root = -1;
  std::vector<int> left, right, parent, size;

  // @note The smallest element becomes the root. For equivalent elements, the one
  // with the smaller index is treated as smaller.
  // @note `parent[root]` is `-1`
  template <class T, class Comp = std::less<T>>
  void build(const std::vector<T>& a, Comp comp = Comp()) {
    if (a.empty()) return;
    int n = int(a.size());
    left.assign(n, -1);
    right.assign(n, -1);
    parent.resize(n);
    size.resize(n);
    std::vector<int> st;
    for (int i = 0; i < n; i++) {
      int k = -1;
      while (!st.empty() && comp(a[i], a[st.back()])) {
        k = st.back();
        update(k);
        st.pop_back();
      }
      if (!st.empty()) right[st.back()] = i;
      left[i] = k;
      st.push_back(i);
    }
    for (int i = int(st.size()) - 1; i >= 0; i--) {
      update(st[i]);
    }
    root = st[0];
    parent[root] = -1;
  }

 private:
  void update(int k) {
    size[k] = 1;
    if (left[k] != -1) {
      parent[left[k]] = k;
      size[k] += size[left[k]];
    }
    if (right[k] != -1) {
      parent[right[k]] = k;
      size[k] += size[right[k]];
    }
  }
};

}  // namespace cp