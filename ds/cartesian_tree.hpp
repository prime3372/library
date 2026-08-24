#pragma once

#include <cassert>
#include <vector>

namespace cp {

template <bool root_is_max> class cartesian_tree {
 public:
  cartesian_tree() {}
  template <class T> explicit cartesian_tree(const std::vector<T>& a) {
    build(a);
  }

  int root = -1;
  std::vector<int> left, right, parent, size;

  template <class T> void build(const std::vector<T>& a) {
    assert(!a.empty());

    int n = int(a.size());
    left.assign(n, -1);
    right.assign(n, -1);
    size.resize(n);
    std::vector<int> st;
    for (int i = 0; i < n; i++) {
      int k = -1;
      while (!st.empty()) {
        if (root_is_max && a[st.back()] >= a[i]) break;
        if (!root_is_max && a[st.back()] <= a[i]) break;
        k = st.back();
        size[k] = 1;
        if (left[k] != -1) size[k] += size[left[k]];
        if (right[k] != -1) size[k] += size[right[k]];
        st.pop_back();
      }
      if (!st.empty()) right[st.back()] = i;      
      left[i] = k;
      st.push_back(i);
    }
    for (int i = int(st.size()) - 1; i >= 0; i--) {
      int k = st[i];
      size[k] = 1;
      if (left[k] != -1) size[k] += size[left[k]];
      if (right[k] != -1) size[k] += size[right[k]];
    }
    root = st[0];

    parent.resize(n);
    for (int i = 0; i < n; i++) {
      if (left[i] != -1) parent[left[i]] = i;
      if (right[i] != -1) parent[right[i]] = i;
    }
    parent[root] = -1;
  }
};

}  // namespace cp