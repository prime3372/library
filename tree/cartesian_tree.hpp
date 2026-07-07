#pragma once

#include <cassert>
#include <vector>

namespace cp {

template <bool root_is_min> struct cartesian_tree {
  int root;
  std::vector<int> left, right, parent;
  
  cartesian_tree() {}
  template <class T> explicit cartesian_tree(const std::vector<T>& a) { build(a); }
  
  template <class T> void build(const std::vector<T>& a) {
    assert(!a.empty());
    int n = int(a.size());
    left.assign(n, -1);
    right.assign(n, -1);
    std::vector<int> st;
    for (int i = 0; i < n; i++) {
      int k = -1;
      while (!st.empty()) {
        if constexpr (root_is_min) {
          if (a[st.back()] <= a[i]) break;
        } else {
          if (a[st.back()] >= a[i]) break;
        }
        int j = st.back();
        st.pop_back();
        right[j] = k;
        k = j;
      }
      left[i] = k;
      st.push_back(i);
    }
    
    for(int i = 0; i < int(st.size()) - 1; i++) {
      right[st[i]] = st[i + 1];
    }
    root = st[0];
    
    parent.resize(n);
    for (int i = 0; i < n; i++) {
      if (left[i] != -1) parent[left[i]] = i;
      if (right[i] != -1) parent[right[i]] = i;
    }
    parent[root] = root;
  }
};

} // namespace cp