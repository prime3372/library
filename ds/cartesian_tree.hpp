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

  // @note parent[root] = -1
  template <class T> void build(const std::vector<T>& a) {
    assert(!a.empty());

    int n = int(a.size());
    left.assign(n, -1);
    right.assign(n, -1);
    parent.resize(n);
    size.resize(n);
    std::vector<int> st;
    for (int i = 0; i < n; i++) {
      int k = -1;
      while (!st.empty()) {
        if (root_is_max && a[st.back()] >= a[i]) break;
        if (!root_is_max && a[st.back()] <= a[i]) break;
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